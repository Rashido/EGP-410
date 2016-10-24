#include "AlignmentSteering.h"

#include "KinematicUnit.h"
#include "UnitManager.h"

AlignmentSteering::AlignmentSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float alignRadius = 75.0f)
{
	mpMover = pMover;
	mpUnitList = unitList;
	mAlignRadius = alignRadius;
}

Steering* AlignmentSteering::getSteering()
{
	for (auto it : *mpUnitList)
	{
		if (it.first != "player" && it.second != mpMover)
		{
			if ((mpMover->getPosition() - it.second->getPosition()).getLength() < mAlignRadius)
			{
				mLinear += it.second->getVelocity();
				++mNeighborCount;
			}
		}
	}

	if (mNeighborCount == 0)
		return this;

	mLinear /= mNeighborCount;
	mLinear.normalize();
	return this;
}