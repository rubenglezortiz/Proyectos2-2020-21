#include "Ability_Kirin.h"


void Ability_Kirin::AbilityExecute(int x, int y)
{
	auto& pos = entity_->getComponent<Transform>()->getPos();
	map->removeCharacter(map->SDLPointToMapCoords(pos));
	pos.setX(x * cellWidth + OFFSET_X);
	pos.setY(y * cellHeight + OFFSET_Y + OFFSET_TOP);
	map->setCharacter(map->SDLPointToMapCoords(pos), entity_);
	sdlutils().soundEffects().at("kirinSound").setChunkVolume(5);
	sdlutils().soundEffects().at("kirinSound").play(); //-----------------------------------------------------------		
}