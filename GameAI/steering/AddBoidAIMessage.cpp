#include "AddBoidAIMessage.h"

#include "Game.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "StateManager.h"

AddBoidAIMessage::AddBoidAIMessage()
:GameMessage(ADD_DYNAMIC_ARRIVE_AI_MESSAGE)
{

}

AddBoidAIMessage::~AddBoidAIMessage()
{

}

void AddBoidAIMessage::process()
{
	std::string id = "ai" + std::to_string(gpGame->getUnitManager()->getUnitCount());
	Vector2D pos = Vector2D(500, 400);
	Vector2D vel = Vector2D(0.0f, 0.0f);

	gpGame->getUnitManager()->addUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), pos, vel, gpGame->getStateManager()->getVelocity(), gpGame->getStateManager()->getRadius(), gpGame->getStateManager()->getAngularVelocity(), 100.0f, id);
	gpGame->getUnitManager()->setUnitBehavior(BOID, id, "");
}