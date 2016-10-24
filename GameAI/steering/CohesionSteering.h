#ifndef COHESION_STEERING
#define COHESION_STEERING

#include "Steering.h"
#include <map>

class KinematicUnit;

class CohesionSteering :public Steering
{
public:
	CohesionSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float cohesionRadius = 300.0f);
	~CohesionSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	std::map<std::string, KinematicUnit*>* mpUnitList;
	float mCohesionRadius;
	int mNeighborCount = 0;
};

#endif