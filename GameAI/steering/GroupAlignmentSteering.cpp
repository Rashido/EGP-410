#include "GroupAlignmentSteering.h"

#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeperationSteering.h"
#include "KinematicWanderSteering.h"

#include "KinematicUnit.h"

GroupAlignmentSteering::GroupAlignmentSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float reactionRadius)
{
	mApplyDirectly = false;

	mpMover = pMover;
	mpUnitList = unitList;
	mReactionRadius = reactionRadius;

	mpAlignment = new AlignmentSteering(mpMover, mpUnitList, mReactionRadius);
	mpSeperation = new SeperationSteering(mpMover, mpUnitList, mReactionRadius);
	mpCohesion = new CohesionSteering(mpMover, mpUnitList, mReactionRadius);
	mpWander = new KinematicWanderSteering(mpMover);
}

GroupAlignmentSteering::~GroupAlignmentSteering()
{
	delete mpAlignment;
	delete mpSeperation;
	delete mpCohesion;
	delete mpWander;
}

Steering* GroupAlignmentSteering::getSteering()
{
	mpAlignment->getSteering();
	mpSeperation->getSteering();
	mpCohesion->getSteering();
	mpWander->getSteering();

	mLinear += mpAlignment->getLinear() + mpSeperation->getLinear() + mpCohesion->getLinear() + mpWander->getLinear();
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();

	mAngular = 0;

	return this;
}