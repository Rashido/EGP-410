#ifndef STATE_MANAGER
#define STATE_MANAGER

#include "Trackable.h"
#include <memory>
#include <string>

enum ManagerState
{
	VELOCITY,
	RADIUS,
	ANGULAR
};

class StateManager : public Trackable
{
public:
	StateManager(float defaultVel = 180.0f, float defaultRad = 200.0f, float defaultAngular = 0.0f);
	~StateManager();

	void update();

	void addToAnEnemyStat();
	void subtractFromAnEnemyStat();
	void setState(ManagerState state);
	inline void toggleActive() { mActive = !mActive; };

private:
	ManagerState mState;

	std::shared_ptr<float> mpEnemyVel;
	std::shared_ptr<float> mpEnemyRadius;
	std::shared_ptr<float> mpEnemyAngularVel;

	std::string mCurrentModeText;
	std::string mEnemyVelText;
	std::string mEnemyRadiusText;
	std::string mEnemyAngularVelText;

	bool mActive;
};

#endif