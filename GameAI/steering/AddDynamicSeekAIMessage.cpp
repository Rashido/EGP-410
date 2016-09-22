#include "AddDynamicSeekAIMessage.h"

#include "Game.h"
#include "UnitManager.h"
#include "SpriteManager.h"

AddDynamicSeekAIMessage::AddDynamicSeekAIMessage()
:GameMessage(ADD_DYNAMIC_SEEK_AI_MESSAGE)
{

}

AddDynamicSeekAIMessage::~AddDynamicSeekAIMessage()
{

}

void AddDynamicSeekAIMessage::process()
{
	std::string id = "ai" + std::to_string(gpGame->getUnitManager()->getUnitCount());
	Vector2D pos = Vector2D(gpGame->getUnitManager()->getUnit("player")->getPosition().getX() + 100, gpGame->getUnitManager()->getUnit("player")->getPosition().getY());
	Vector2D vel = Vector2D(0.0f, 0.0f);

	gpGame->getUnitManager()->addUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), pos, vel, 180.0f, 100.0f, id);
	gpGame->getUnitManager()->setUnitBehavior(DYNAMIC_SEEK, id, "player");

}