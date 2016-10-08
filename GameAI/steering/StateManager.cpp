#include "StateManager.h"
#include "Game.h"

#include <allegro5\allegro.h>
#include <sstream>
#include <iomanip>

StateManager::StateManager(float defaultVel, float defaultRad, float defaultAngular, bool defaultShowBox):
mpEnemyVel(new float(defaultVel)),
mpEnemyRadius(new float(defaultRad)),
mpEnemyAngularVel(new float(defaultAngular)),
mpShowCollisionBoxes(new bool(defaultShowBox))
{
	//init strings
	setState(VELOCITY); //note to self, mActive is defaultly true so this will still init mCurrentModeText
	
	std::stringstream ss;

	ss << std::fixed << std::setprecision(1) << *mpEnemyVel;
	mEnemyVelText = "Enemy Velocity: " + ss.str();
	ss.str(std::string());

	ss << std::fixed << std::setprecision(1) << *mpEnemyRadius;
	mEnemyRadiusText = "Enemy Reaction Radius: " + ss.str();
	ss.str(std::string());

	ss << std::fixed << std::setprecision(1) << *mpEnemyAngularVel;
	mEnemyAngularVelText = "Enemy Angular Velocity: " + ss.str();
	ss.str(std::string());

	mCollisionDebugText = "Collision Debug: Off";

	mActive = false;
}

StateManager::~StateManager()
{

}

void StateManager::update()
{
	if (mActive)
	{
		//draw strings
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 5, 0, ALLEGRO_ALIGN_LEFT, mCurrentModeText.c_str());
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 5, 20, ALLEGRO_ALIGN_LEFT, mEnemyVelText.c_str());
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 5, 40, ALLEGRO_ALIGN_LEFT, mEnemyRadiusText.c_str());
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 5, 60, ALLEGRO_ALIGN_LEFT, mEnemyAngularVelText.c_str());
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), 5, 80, ALLEGRO_ALIGN_LEFT, mCollisionDebugText.c_str());
	}
}

void StateManager::addToAnEnemyStat()
{
	if (mActive)
	{
		std::stringstream ss;

		switch (mState)
		{
		case VELOCITY:
			*mpEnemyVel += 10.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyVel;
			mEnemyVelText = "Enemy Velocity: " + ss.str();
			ss.str(std::string());
			break;
		case RADIUS:
			*mpEnemyRadius += 10.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyRadius;
			mEnemyRadiusText = "Enemy Reaction Radius: " + ss.str();
			ss.str(std::string());
			break;
		case ANGULAR:
			*mpEnemyAngularVel += 5.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyAngularVel;
			mEnemyAngularVelText = "Enemy Angular Velocity: " + ss.str();
			ss.str(std::string());
			break;
		case COLLISION_BOXES:
			*mpShowCollisionBoxes = true;
			mCollisionDebugText = "Collision Debug: On";
			break;
			
		}
	}
}

void StateManager::subtractFromAnEnemyStat()
{
	if (mActive)
	{
		std::stringstream ss;

		switch (mState)
		{
		case VELOCITY:
			*mpEnemyVel -= 10.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyVel;
			mEnemyVelText = "Enemy Velocity: " + ss.str();
			ss.str(std::string());
			break;
		case RADIUS:
			*mpEnemyRadius -= 10.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyRadius;
			mEnemyRadiusText = "Enemy Reaction Radius: " + ss.str();
			ss.str(std::string());
			break;
		case ANGULAR:
			*mpEnemyAngularVel -= 5.0f;
			ss << std::fixed << std::setprecision(1) << *mpEnemyAngularVel;
			mEnemyAngularVelText = "Enemy Angular Velocity: " + ss.str();
			ss.str(std::string());
		case COLLISION_BOXES:
			*mpShowCollisionBoxes = false;
			mCollisionDebugText = "Collision Debug: Off";
			break;
		}
	}
}

void StateManager::setState(ManagerState state)
{
	if (mActive)
	{
		mState = state;
		mCurrentModeText = "Current Mode: ";

		switch (mState)
		{
		case VELOCITY:
			mCurrentModeText += "Velocity";
			break;
		case RADIUS:
			mCurrentModeText += "Reaction Radius";
			break;
		case ANGULAR:
			mCurrentModeText += "Angular Velocity";
			break;
		case COLLISION_BOXES:
			mCurrentModeText += "Collision Box Debug";
			break;
		}
	}
}
