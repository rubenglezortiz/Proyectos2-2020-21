#include "Ability_Kirin.h"


void AbilityKirin(int x, int y, AbilityStruct* info)
{
	GameMap* map = info->getAbility()->getMap();
	Entity* entity_ = info->getAbility()->getEntity();

	auto& pos = entity_->getComponent<Transform>()->getPos();
	map->removeCharacter(map->SDLPointToMapCoords(pos));
	pos.setX(x * map->getCellWidth() + OFFSET_X);
	pos.setY(y * map->getCellHeight() + OFFSET_Y + OFFSET_TOP);	
	map->setCharacter(map->SDLPointToMapCoords(pos), entity_);
	//sdlutils().soundEffects().at("kirinSound").setChunkVolume(5);
	sdlutils().soundEffects().at("kirinSound").play(); 
}

Ability_Kirin::Ability_Kirin() : AbilityStruct(selector, ShaderForm::Cross, ShaderType::KirinSh, 2) 
{ 
	setAbility([](int x, int y, AbilityStruct* info) {
		AbilityKirin(x,y,info);
		});
}
