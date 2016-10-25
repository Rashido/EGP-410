#ifndef STATE_MANAGER
#define STATE_MANAGER

#include "Trackable.h"
#include <string>
#include <memory>

enum ManagerState
{
	VELOCITY,
	RADIUS,
	ANGULAR,
	COLLISION_BOXES
};

class StateManager : public Trackable
{
public:
	StateManager(float defaultVel = 180.0f, float defaultRad = 200.0f, float defaultAngular = 25.0f, bool defaultShowBox = false);
	~StateManager();

	void update();

	void addToAnEnemyStat();
	void subtractFromAnEnemyStat();
	void setState(ManagerState state);
	inline void toggleActive() { mActive = !mActive; };

	inline std::shared_ptr<float> getVelocity() { return mpEnemyVel; }; 
	inline std::shared_ptr<float> getRadius(){ return mpEnemyRadius; };
	inline std::shared_ptr<float> getAngularVelocity() { return mpEnemyAngularVel; };
	inline std::shared_ptr<bool> getCollisionBoxes() { return mpShowCollisionBoxes; };

private:
	ManagerState mState;

	std::shared_ptr<float> mpEnemyVel;
	std::shared_ptr<float> mpEnemyRadius;
	std::shared_ptr<float> mpEnemyAngularVel;
	std::shared_ptr<bool> mpShowCollisionBoxes;

	std::string mCurrentModeText;
	std::string mEnemyVelText;
	std::string mEnemyRadiusText;
	std::string mEnemyAngularVelText;
	std::string mCollisionDebugText;

	bool mActive;
};

#endif