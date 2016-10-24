#include "Game.h"
#include "Kinematic.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "WallManager.h"
#include "Steering.h"
#include "KinematicSeekSteering.h"
#include "KinematicArriveSteering.h"
#include "KinematicWanderSteering.h"
#include "DynamicSeekSteering.h"
#include "DynamicArriveSteering.h"
#include "WanderAndSeekSteering.h"
#include "CollisionAvoidanceSteering.h"
#include "GroupAlignmentSteering.h"

#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"

using namespace std;

Steering gNullSteering( gZeroVector2D, 0.0f );

KinematicUnit::KinematicUnit(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, std::shared_ptr<float> maxVelocity, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration, bool isPlayer)
:Kinematic(position, orientation, velocity, rotationVel)
, mpSprite(pSprite)
, mpCurrentSteering(NULL)
, mMaxVelocity(maxVelocity)
, mReactionRadius(reactionRadius)
, mMaxRotationalVelocity(maxRotational)
, mMaxAcceleration(maxAcceleration)
, mPlayer(isPlayer)
{
	mpCollisionAvoidance = new CollisionAvoidanceSteering(this, gpGame->getUnitManager()->getMap());
	mHitbox = Hitbox(Vector2D(position.getX()-16, position.getY()-16), 32, 32); //32 is the length and width of the arrow sprite
}

KinematicUnit::~KinematicUnit()
{
	delete mpCurrentSteering;
	delete mpCollisionAvoidance;
}

void KinematicUnit::draw( GraphicsBuffer* pBuffer )
{
	mpSprite->draw( *pBuffer, mPosition.getX(), mPosition.getY(), mOrientation );
	mHitbox.draw();
}

void KinematicUnit::update(float time)
{
	Vector2D tempPos = mPosition;

	Steering* steering;
	//check for collision with other units
	mpCollisionAvoidance->updateSteering();
	if (!mPlayer && mpCollisionAvoidance->getDanger()) //if in danger set steering to avoidance
	{
		steering = mpCollisionAvoidance;		
	}
	else //otherwise proceed normally
	{
		if (mpCurrentSteering != NULL)
		{
			steering = mpCurrentSteering->getSteering();
		}
		else
		{
			steering = &gNullSteering;
		}
	}

	if( steering->shouldApplyDirectly() )
	{
		//not stopped
		if( getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED )
		{
			setVelocity( steering->getLinear() );
			setOrientation( steering->getAngular() );
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity( 0.0f );
		steering->setAngular( 0.0f );
	}

	//check if colliding with wall
	if (checkCollisionWithWalls())
	{
		Vector2D newVel;
		if (mPlayer) //player bounce behavior. A bit wonky but gets the job done
		{
			if (mBounceVertically)
			{
				GameMessage* pMessage;
				if (mPosition.getY() < 500)
					pMessage = new PlayerMoveToMessage(Vector2D(mPosition.getX(), mPosition.getY() + 50));
				else
					pMessage = new PlayerMoveToMessage(Vector2D(mPosition.getX(), mPosition.getY() - 50));

				gpGame->getMessageManager()->addMessage(pMessage, 0);
				newVel = Vector2D(mVelocity.getX(), -(mVelocity.getY()*2));
			}
			else
			{
				GameMessage* pMessage;
				if (mPosition.getX() < 400)
					pMessage = new PlayerMoveToMessage(Vector2D(mPosition.getX() + 50, mPosition.getY()));
				else
					pMessage = new PlayerMoveToMessage(Vector2D(mPosition.getX() - 50, mPosition.getY()));

				gpGame->getMessageManager()->addMessage(pMessage, 0);
				newVel = Vector2D(-(mVelocity.getX()*2), mVelocity.getY());
			}
		}
		else //normal behavior for AI units
		{
			if (mBounceVertically)
			{
				newVel = Vector2D(mVelocity.getX(), -(mVelocity.getY()));
			}
			else
			{
				newVel = Vector2D(-(mVelocity.getX()), mVelocity.getY());
			}
		}

		mVelocity = newVel;
	}
	//move the unit using current velocities
	Kinematic::update( time );
	//calculate new velocities
	calcNewVelocities( *steering, time, *mMaxVelocity, *mMaxRotationalVelocity );
	//update hitbox location
	tempPos = mPosition - tempPos;
	mHitbox.update(tempPos.getX(), tempPos.getY());
	//move to oposite side of screen if we are off
	GRAPHICS_SYSTEM->wrapCoordinates( mPosition );

	//set the orientation to match the direction of travel
	//setNewOrientation();
}

bool KinematicUnit::checkCollisionWithWalls()
{
	for (int i = 0; i < gpGame->getWallManager()->getNumOfWalls(); i++)
	{
		if (mHitbox.checkCollision(gpGame->getWallManager()->getWall(i)->getHitbox()))
		{
			if (gpGame->getWallManager()->getWall(i)->getBounceType() == VERTICAL)
			{
				mBounceVertically = true;
			}
			else
			{
				mBounceVertically = false;
			}

			return true;
		}
	}

	return false;
}

//private - deletes old Steering before setting
void KinematicUnit::setSteering( Steering* pSteering )
{
	delete mpCurrentSteering;
	mpCurrentSteering = pSteering;
}

void KinematicUnit::setNewOrientation()
{ 
	mOrientation = getOrientationFromVelocity( mOrientation, mVelocity ); 
}

void KinematicUnit::seek(const Vector2D &target)
{
	KinematicSeekSteering* pSeekSteering = new KinematicSeekSteering( this, target );
	setSteering( pSeekSteering );
}

void KinematicUnit::arrive(const Vector2D &target)
{
	KinematicArriveSteering* pArriveSteering = new KinematicArriveSteering( this, target );
	setSteering( pArriveSteering );
}

void KinematicUnit::wander()
{
	KinematicWanderSteering* pWanderSteering = new KinematicWanderSteering( this );
	setSteering( pWanderSteering );
}

void KinematicUnit::dynamicSeek( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, pTarget );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicFlee( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, pTarget, true );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicArrive( KinematicUnit* pTarget )
{
	DynamicArriveSteering* pDynamicArriveSteering = new DynamicArriveSteering( this, pTarget );
	setSteering( pDynamicArriveSteering );
}

void KinematicUnit::wanderAndSeek(KinematicUnit* pTarget)
{
	WanderAndSeekSteering* pWanderAndSeekSteering = new WanderAndSeekSteering(this, pTarget, mReactionRadius);
	setSteering(pWanderAndSeekSteering);
}

void KinematicUnit::wanderAndFlee(KinematicUnit* pTarget)
{
	WanderAndSeekSteering* pWanderAndSeekSteering = new WanderAndSeekSteering(this, pTarget, mReactionRadius, true);
	setSteering(pWanderAndSeekSteering);
}

void KinematicUnit::boid()
{
	GroupAlignmentSteering* pBoidSteering = new GroupAlignmentSteering(this, gpGame->getUnitManager()->getMap(), 25);
	setSteering(pBoidSteering);
}
