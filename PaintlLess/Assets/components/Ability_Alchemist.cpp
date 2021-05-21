#include "Ability_Alchemist.h"

void AbilityAlchemist(int x, int y, AbilityStruct* info)
{
	GameMap* map = info->getAbility()->getMap();
	Entity* entity_ = info->getAbility()->getEntity();
	if (map->getCharacter(Vector2D(x, y))->hasComponent<Movimiento>()) {
		entity_->getComponent<FramedImage>()->setAnim(A_A_A);
		map->getCharacter(Vector2D(x, y))->getComponent<Movimiento>()->setStun(2);
		sdlutils().soundEffects().at("alquimistaSound").play(); //-----------------------------------------------------------	
	}	
	sdlutils().soundEffects().at("alquimistaSound").setChunkVolume(30);	
}

Ability_Alchemist::Ability_Alchemist() : AbilityStruct(selectorA, ShaderForm::Cross, ShaderType::AttackSh) 
{
	setAbility(AbilityAlchemist);
}