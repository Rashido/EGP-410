#include "UnitManager.h"

#include "Game.h"
#include "GraphicsSystem.h"
#include "Sprite.h"

#include <time.h>
#include <stdlib.h>

UnitManager::UnitManager()
{
	mUnitCount = 0;

	srand(time(NULL)); //seed for random deletion
}

UnitManager::~UnitManager()
{
	cleanUp();
}

void UnitManager::addUnit(Sprite* sprite, Vector2D& pos, Vector2D& vel, std::shared_ptr<float> maxVel, float maxAcc,  std::string id)
{
	mUnitList.emplace(id, new KinematicUnit(sprite, pos, 1, vel, 0.0f, maxVel, maxAcc));
	mUnitCount++;
}

void UnitManager::removeUnit(std::string id)
{
	delete mUnitList[id];
	mUnitList.erase(id);
}

void UnitManager::setUnitBehavior(BehaviorType type, std::string entityID, std::string targetID)
{
	switch (type)
	{
		case DYNAMIC_ARRIVE:
			mUnitList[entityID]->dynamicArrive(mUnitList[targetID]);
			break;
		case DYNAMIC_SEEK:
			mUnitList[entityID]->dynamicSeek(mUnitList[targetID]);
			break;
		case WANDER_AND_SEEK:
			mUnitList[entityID]->wanderAndSeek(mUnitList[targetID]);
			break;
		case WANDER_AND_FLEE:
			mUnitList[entityID]->wanderAndFlee(mUnitList[targetID]);
			break;
	}
}

KinematicUnit* UnitManager::getUnit(std::string id)
{
	return mUnitList[id];
}

bool UnitManager::deleteRandomAIUnit()
{
	std::string idCheck = "";

	//if only the player is left, tell the message to exit the game
	if (mUnitList.size() <= 1)
	{
		return true;
	}
	else
	{
		do
		{
			auto it = mUnitList.begin();
			std::advance(it, rand() % mUnitList.size());

			idCheck = it->first;

			if (idCheck != "player") 
				removeUnit(idCheck);

		} while (idCheck == "player");

		return false; //continue game
	}	
}

void UnitManager::update(double timePassed)
{

	for (std::map<std::string, KinematicUnit*>::iterator i = mUnitList.begin(); i != mUnitList.end(); ++i)
	{
		i->second->update(timePassed);
	}
}

void UnitManager::draw()
{
	for (std::map<std::string, KinematicUnit*>::iterator i = mUnitList.begin(); i != mUnitList.end(); ++i)
	{
		i->second->draw(gpGame->getGraphicsSystem()->getBackBuffer());
	}
}

void UnitManager::cleanUp()
{
	for (std::map<std::string, KinematicUnit*>::iterator i = mUnitList.begin(); i != mUnitList.end(); ++i)
	{
		delete i->second;
	}

	mUnitList.clear();
}