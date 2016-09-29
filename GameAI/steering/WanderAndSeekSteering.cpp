#include "WanderAndSeekSteering.h"
#include "KinematicUnit.h"
#include "Game.h"

WanderAndSeekSteering::WanderAndSeekSteering(KinematicUnit *pMover, KinematicUnit* pTarget, float targetRadius, bool shouldFlee)
:mpMover(pMover)
, mpTarget(pTarget)
, mShouldFlee(shouldFlee)
{
	mApplyDirectly = false;
}

Steering* WanderAndSeekSteering::getSteering()
{
	Vector2D direction = mpTarget->getPosition() - mpMover->getPosition();
	float distance = direction.getLength();

	//if in target radius, perform seek or flee behavior
	if (distance < mTargetRadius)
	{
		if (!mShouldFlee)
		{
			mLinear = mpTarget->getPosition() - mpMover->getPosition();
		}
		else
		{
			mLinear = mpMover->getPosition() - mpTarget->getPosition();
		}

		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;
		return this;
	}
	else //else perform wander behavior
	{
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);
		return this;
	}
}