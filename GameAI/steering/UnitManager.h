#ifndef UNIT_MANAGER
#define UNIT_MANAGER

#include <Trackable.h>
#include <Vector2D.h>
#include <map>

#include "KinematicUnit.h"

class Sprite;

enum BehaviorType
{
	DYNAMIC_ARRIVE,
	DYNAMIC_SEEK,
	WANDER_AND_SEEK,
	WANDER_AND_FLEE
};

class UnitManager :public Trackable
{
public:
	UnitManager();
	~UnitManager();

	void addUnit(Sprite* sprite, Vector2D& pos, Vector2D& vel, float maxVel, float maxAcc, std::string id);
	void removeUnit(std::string id);
	void setUnitBehavior(BehaviorType type, std::string entityID, std::string targetID);
	KinematicUnit* getUnit(std::string id);
	bool deleteRandomAIUnit();
	inline int getUnitCount(){ return mUnitCount; };

	void update(double timePassed);
	void draw();
	void cleanUp();

private:
	std::map<std::string, KinematicUnit*> mUnitList;

	int mUnitCount;
};

#endif