#include "CohesionSteering.h"

#include "KinematicUnit.h"
#include "UnitManager.h"

CohesionSteering::CohesionSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float cohesionRadius)
{
	mpMover = pMover;
	mpUnitList = unitList;
	mCohesionRadius = cohesionRadius;
}

Steering* CohesionSteering::getSteering()
{
	int neighborCount = 0;
	mLinear = Vector2D(0, 0);

	for (auto it : *mpUnitList)
	{
		if (it.first != "player" && it.second != mpMover)
		{
			if ((mpMover->getPosition() - it.second->getPosition()).getLength() < mCohesionRadius && 
				(mpMover->getPosition() - it.second->getPosition()).getLength() > -mCohesionRadius)
			{
				//ASSEMBLY HERE
				float tmpLinearX = mLinear.mX; float tmpLinearY = mLinear.mY;
				float tmpPosX = it.second->getPosition().mX; float tmpPosY = it.second->getPosition().mY;

				float count = 1;

				__asm
				{
					movss xmm0, tmpLinearX
					movss xmm1, tmpPosX
					addss xmm0, xmm1
					movss tmpLinearX, xmm0

					movss xmm0, tmpLinearY
					movss xmm1, tmpPosY
					addss xmm0, xmm1
					movss tmpLinearY, xmm0

					movss xmm0, neighborCount
					movss xmm1, count
					addss xmm0, xmm1
					movss neighborCount, xmm0

				}

				mLinear.mX = tmpLinearX;
				mLinear.mY = tmpLinearY;

				//mLinear += it.second->getPosition();
				//++neighborCount;
			}
		}
	}

	if (neighborCount == 0)
		return this;

	//MORE ASSEMBLY
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

	float tmpPosX = mpMover->getPosition().mX; float tmpPosY = mpMover->getPosition().mY;

	__asm
	{
		movss xmm0, tmpLinearX
		movss xmm1, tmpPosX
		subss xmm0, xmm1
		movss tmpLinearX, xmm0

		movss xmm0, tmpLinearY
		movss xmm1, tmpPosY
		subss xmm0, xmm1
		movss tmpLinearY, xmm0
	}

	mLinear.mX = tmpLinearX;
	mLinear.mY = tmpLinearY;
	//mLinear = mLinear - mpMover->getPosition();

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