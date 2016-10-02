#include "StateManager.h"

StateManager::StateManager(float defaultVel, float defaultRad, float defaultAngular)
{
	auto mpEnemyVel = std::make_shared<float>(defaultVel);
	auto mpEnemyRad = std::make_shared<float>(defaultRad);
	auto mpEnemyAngularVel = std::make_shared<float>(defaultAngular);

	mState = VELOCITY;
}

StateManager::~StateManager()
{

}

void StateManager::update()
{
	if (mActive)
	{
		//draw strings
	}
}

void StateManager::addToAnEnemyStat()
{
	if (mActive)
	{
		switch (mState)
		{
		case VELOCITY:
			*mpEnemyVel += 5.0f;
			mEnemyVelText = "Enemy Velocity: " + std::to_string(*mpEnemyVel);
			break;
		case RADIUS:
			*mpEnemyRadius += 5.0f;
			mEnemyRadiusText = "Enemy Reaction Radius: " + std::to_string(*mpEnemyRadius);
			break;
		case ANGULAR:
			*mpEnemyAngularVel += 3.0f;
			mEnemyAngularVelText = "Enemy Angular Velocity: " + std::to_string(*mpEnemyAngularVel);
		}
	}
}

void StateManager::subtractFromAnEnemyStat()
{
	if (mActive)
	{
		switch (mState)
		{
		case VELOCITY:
			*mpEnemyVel -= 5.0f;
			mEnemyVelText = "Enemy Velocity: " + std::to_string(*mpEnemyVel);
			break;
		case RADIUS:
			*mpEnemyRadius -= 5.0f;
			mEnemyRadiusText = "Enemy Reaction Radius: " + std::to_string(*mpEnemyRadius);
			break;
		case ANGULAR:
			*mpEnemyAngularVel -= 3.0f;
			mEnemyAngularVelText = "Enemy Angular Velocity: " + std::to_string(*mpEnemyAngularVel);
		}
	}
}