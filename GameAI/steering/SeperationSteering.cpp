#include "SeperationSteering.h"

#include "KinematicUnit.h"
#include "UnitManager.h"

SeperationSteering::SeperationSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float seperationRadius)
{
	mpMover = pMover;
	mpUnitList = unitList;
	mAlignRadius = seperationRadius;
}

Steering* SeperationSteering::getSteering()
{
	for (auto it : *mpUnitList)
	{
		if (it.first != "player" && it.second != mpMover)
		{
			if ((mpMover->getPosition() - it.second->getPosition()).getLength() < mAlignRadius)
			{
				mLinear += mpMover->getPosition() - it.second->getPosition();
			}
		}
	}

	if (mNeighborCount == 0)
		return this;

	mLinear /= mNeighborCount;
	mLinear.normalize();
	return this;
}