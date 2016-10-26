#include "GroupAlignmentSteering.h"

#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeperationSteering.h"
#include "KinematicWanderSteering.h"

#include "KinematicUnit.h"

GroupAlignmentSteering::GroupAlignmentSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList)
{
	mApplyDirectly = false;

	mpMover = pMover;
	mpUnitList = unitList;

	mpAlignment = new AlignmentSteering(mpMover, mpUnitList);
	mpSeperation = new SeperationSteering(mpMover, mpUnitList);
	mpCohesion = new CohesionSteering(mpMover, mpUnitList);

	mAlignmentWeight = 2;
	mSeperationWeight = 3.5;
	mCohesionWeight = 2;
}

GroupAlignmentSteering::~GroupAlignmentSteering()
{
	delete mpAlignment;
	delete mpSeperation;
	delete mpCohesion;
}

Steering* GroupAlignmentSteering::getSteering()
{
	mpAlignment->getSteering();
	mpSeperation->getSteering();
	mpCohesion->getSteering();

	mLinear = mpCohesion->getLinear() * mCohesionWeight + mpSeperation->getLinear() * mSeperationWeight + mpAlignment->getLinear() * mAlignmentWeight;
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();

	mAngular = 0;

	return this;
}