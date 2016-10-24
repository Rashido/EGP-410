#ifndef ALIGNMENT_STEERING
#define ALIGNMENT_STEERING

#include "Steering.h"
#include <map>

class KinematicUnit;

class AlignmentSteering :public Steering
{
public:
	AlignmentSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float alignRadius = 300.0f);
	~AlignmentSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	std::map<std::string, KinematicUnit*>* mpUnitList;
	float mAlignRadius;
	int mNeighborCount = 0;
};

#endif