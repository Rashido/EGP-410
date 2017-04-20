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
	int neighborCount = 0;
	mLinear = Vector2D(0, 0);

	for (auto it : *mpUnitList)
	{
		if (it.first != "player" && it.second != mpMover)
		{
			if ((mpMover->getPosition() - it.second->getPosition()).getLength() < mAlignRadius && 
				(mpMover->getPosition() - it.second->getPosition()).getLength() > -mAlignRadius)
			{
				float tmpLinearX = mLinear.mX; float tmpLinearY = mLinear.mY;
				float tmpMoverPosX = mpMover->getPosition().mX; float tmpMoverPosY = mpMover->getPosition().mY;
				float itPosX = it.second->getPosition().mX; float itPosY = it.second->getPosition().mY;
				float count = 1;
				__asm
				{
					movss xmm0, tmpMoverPosX
					movss xmm1, itPosX
					subss xmm0, xmm1
					movss xmm1, tmpLinearX
					addss xmm0, xmm1
					movss tmpLinearX, xmm0

					movss xmm0, tmpMoverPosY
					movss xmm1, itPosY
					subss xmm0, xmm1
					movss xmm1, tmpLinearY
					addss xmm0, xmm1
					movss tmpLinearY, xmm0

					movss xmm0, neighborCount
					movss xmm1, count
					addss xmm0, xmm1
					movss neighborCount, xmm0
				}

				mLinear.mX = tmpLinearX;
				mLinear.mY = tmpLinearY;

				//mLinear += mpMover->getPosition() - it.second->getPosition();
				//++neighborCount;
			}
		}
	}

	if (neighborCount == 0)
		return this;

	float tmpLinearX = mLinear.mX; float tmpLinearY = mLinear.mY;

	__asm
	{
		movss xmm0, tmpLinearX
		movss xmm1, neighborCount
		divss xmm0, xmm1
		movss tmpLinearX, xmm0

		movss xmm0, tmpLinearY
		movss xmm1, neighborCount
		divss xmm0, xmm1
		movss tmpLinearY, xmm0
	}

	mLinear.mX = tmpLinearX;
	mLinear.mY = tmpLinearY;

	//mLinear /= neighborCount;

	tmpLinearX = mLinear.mX; tmpLinearY = mLinear.mY;
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

	mLinear.mX = tmpLinearX;
	mLinear.mY = tmpLinearY;

	//mLinear.normalize();
	return this;
}