#ifndef KINEMATIC_WANDER_H
#define KINEMATIC_WANGER_H

#include "Steering.h"

class KinematicUnit;

const float MAX_WANDER_ROTATION = 1.0f;

class KinematicWanderSteering:public Steering
{
public:
	KinematicWanderSteering( KinematicUnit* pMover );
	~KinematicWanderSteering(){};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};

#endif