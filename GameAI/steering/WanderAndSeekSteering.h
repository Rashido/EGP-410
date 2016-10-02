#ifndef WANDER_AND_SEEK_BEHAVIOR
#define WANDER_AND_SEEK_BEHAVIOR

#include "Steering.h"

class KinematicUnit;

const float MAX_WANDER_AND_SEEK_ROTATION = 1.0f;

class WanderAndSeekSteering :public Steering
{
public:
	WanderAndSeekSteering(KinematicUnit* pMove, KinematicUnit* pTarget, bool shouldFlee = false, float targetRadius = 200.0f);
	~WanderAndSeekSteering(){};

	void setTarget(KinematicUnit* pTarget){ mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	float mTargetRadius;
	bool mShouldFlee;
};

#endif