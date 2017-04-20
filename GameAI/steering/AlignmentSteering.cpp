#include "AlignmentSteering.h"

#include "KinematicUnit.h"
#include "UnitManager.h"

AlignmentSteering::AlignmentSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float alignRadius)
{
	mpMover = pMover;
	mpUnitList = unitList;
	mAlignRadius = alignRadius;
}

Steering* AlignmentSteering::getSteering()
{
	int neighborCount = 0;
	mLinear = Vector2D(0, 0);

	for (auto it : *mpUnitList)
	{
		if (it.first != "player" && it.second != mpMover)
		{
			if ((mpMover->getPosition() - it.second->getPosition()).getLength() <= mAlignRadius &&
				(mpMover->getPosition() - it.second->getPosition()).getLength() >= -mAlignRadius)
			{
				//ASSEMBLY HERE
				float tmpLinearX = mLinear.mX; float tmpLinearY = mLinear.mY;
				float tmpVelX = it.second->getVelocity().mX; float tmpVelY = it.second->getVelocity().mY;

				float count = 1;

				__asm
				{
					movss xmm0, tmpLinearX
					movss xmm1, tmpVelX
					addss xmm0, xmm1
					movss tmpLinearX, xmm0

					movss xmm0, tmpLinearY
					movss xmm1, tmpVelY
					addss xmm0, xmm1
					movss tmpLinearY, xmm0	

					movss xmm0, neighborCount
					movss xmm1, count
					addss xmm0, xmm1
					movss neighborCount, xmm0

				}

				mLinear.mX = tmpLinearX;
				mLinear.mY = tmpLinearY;

				//mLinear += it.second->getVelocity();
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

	//EVEN MORE ASSEMBLY
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