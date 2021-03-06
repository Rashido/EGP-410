#include "AddWanderAndSeekAIMessage.h"

#include "Game.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "StateManager.h"

AddWanderAndSeekAIMessage::AddWanderAndSeekAIMessage()
:GameMessage(ADD_WANDER_AND_SEEK_AI_MESSAGE)
{

}

AddWanderAndSeekAIMessage::~AddWanderAndSeekAIMessage()
{

}

void AddWanderAndSeekAIMessage::process()
{
	std::string id = "ai" + std::to_string(gpGame->getUnitManager()->getUnitCount());
	Vector2D pos = Vector2D(gpGame->getUnitManager()->getUnit("player")->getPosition().getX() + 200, gpGame->getUnitManager()->getUnit("player")->getPosition().getY());
	Vector2D vel = Vector2D(0.0f, 0.0f);

	gpGame->getUnitManager()->addUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), pos, vel, gpGame->getStateManager()->getVelocity(), gpGame->getStateManager()->getRadius(), gpGame->getStateManager()->getAngularVelocity(), 100.0f, id);
	gpGame->getUnitManager()->setUnitBehavior(WANDER_AND_SEEK, id, "player");
}