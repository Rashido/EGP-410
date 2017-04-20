#include "GroupAlignmentSteering.h"

#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeperationSteering.h"
#include "KinematicWanderSteering.h"

#include "KinematicUnit.h"

GroupAlignmentSteering::GroupAlignmentSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList,
	std::shared_ptr<float> alignmentWeight, std::shared_ptr<float> seperationWeight, std::shared_ptr<float> cohesionWeight):
	 mpAlignmentWeight(alignmentWeight)
	,mpCohesionWeight(cohesionWeight)
	,mpSeperationWeight(seperationWeight)
{
	mApplyDirectly = false;

	mpMover = pMover;
	mpUnitList = unitList;

	mpAlignment = new AlignmentSteering(mpMover, mpUnitList);
	mpSeperation = new SeperationSteering(mpMover, mpUnitList);
	mpCohesion = new CohesionSteering(mpMover, mpUnitList);
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

	
	float cohesionX = mpCohesion->getLinear().mX, cohesionY = mpCohesion->getLinear().mY,
		seperationX = mpSeperation->getLinear().mX, seperationY = mpSeperation->getLinear().mY,
		alignmentX = mpAlignment->getLinear().mX, alignmentY = mpAlignment->getLinear().mY,
		cWeight = *mpCohesionWeight, sWeight = *mpSeperationWeight, aWeight = *mpAlignmentWeight;

	//mpCohesion->getLinear() * *mpCohesionWeight
	__asm
	{
		movss xmm0, cohesionX
		movss xmm1, cWeight
		mulss xmm0, xmm1
		movss cohesionX, xmm0

		movss xmm0, cohesionY
		movss xmm1, cWeight
		mulss xmm0, xmm1
		movss cohesionY, xmm0
	}

	//mpSeperation->getLinear() * *mpSeperationWeight
	__asm
	{
		movss xmm0, seperationX
		movss xmm1, sWeight
		mulss xmm0, xmm1
		movss seperationX, xmm0

		movss xmm0, seperationY
		movss xmm1, sWeight
		mulss xmm0, xmm1
		movss seperationY, xmm0
	}

	//mpAlignment->getLinear() * *mpAlignmentWeight
	__asm
	{
		movss xmm0, alignmentX
		movss xmm1, aWeight
		mulss xmm0, xmm1
		movss alignmentX, xmm0

		movss xmm0, alignmentY
		movss xmm1, aWeight
		mulss xmm0, xmm1
		movss alignmentY, xmm0
	}

	//addem together
	__asm
	{
		movss xmm0, cohesionX
		movss xmm1, seperationX
		//movss xmm2, alignmentX
		addss xmm0, xmm1
		movss xmm1, alignmentX
		addss xmm0, xmm1
		movss cohesionX, xmm0

		movss xmm0, cohesionY
		movss xmm1, seperationY
		//movss xmm2, alignmentY
		addss xmm0, xmm1
		movss xmm1, alignmentY
		addss xmm0, xmm1
		//addss xmm0, xmm2
		movss cohesionY, xmm0
	}
	mLinear.mX = cohesionX;
	mLinear.mY = cohesionY;

	//mLinear = mpCohesion->getLinear() * *mpCohesionWeight + mpSeperation->getLinear() * *mpSeperationWeight + mpAlignment->getLinear() * *mpAlignmentWeight;

	float tmpLinearX = mLinear.mX, tmpLinearY = mLinear.mY;

	if (mLinear.mX != 0 && mLinear.mY != 0)
	{
		float magnitude;
		__asm
		{
			movss xmm0, tmpLinearX
			movss xmm1, tmpLinearX
			mulss xmm0, xmm1
			movss tmpLinearX, xmm0

			movss xmm0, tmpLinearY
			movss xmm1, tmpLinearY
			mulss xmm0, xmm1
			movss xmm1, xmm0

			movss xmm0, tmpLinearX
			addss xmm0, xmm1
			sqrtss xmm0, xmm0
			movss magnitude, xmm0

		}

		tmpLinearX = mLinear.mX;
		tmpLinearY = mLinear.mY;

		__asm
		{
			movss xmm0, tmpLinearX
			divss xmm0, magnitude
			movss tmpLinearX, xmm0

			movss xmm0, tmpLinearY
			divss xmm0, magnitude
			movss tmpLinearY, xmm0
		}

		//mLinear.normalize();
	}


	float maxVel = mpMover->getMaxVelocity();

	__asm
	{
		movss xmm0, tmpLinearX
		movss xmm1, maxVel
		mulss xmm0, xmm1
		movss tmpLinearX, xmm0

		movss xmm0, tmpLinearY
		movss xmm1, maxVel
		mulss xmm0, xmm1
		movss tmpLinearY, xmm0
	}

	mLinear.mX = tmpLinearX;
	mLinear.mY = tmpLinearY;

	//mLinear *= mpMover->getMaxVelocity();

	mAngular = 0;

	return this;
}