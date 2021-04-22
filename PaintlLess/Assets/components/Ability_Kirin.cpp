#include "Ability_Kirin.h"


void Ability_Kirin::AbilityExecute(int x, int y)
{
	auto& pos = entity_->getComponent<Transform>()->getPos();
	map->removeCharacter(map->SDLPointToMapCoords(pos));
	pos.setX(x * cellWidth);
	pos.setY(y * cellHeight);
	map->setCharacter(map->SDLPointToMapCoords(pos), entity_);
}