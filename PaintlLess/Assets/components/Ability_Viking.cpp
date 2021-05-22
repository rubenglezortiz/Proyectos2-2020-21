#include "Ability_Viking.h"

void AbilityViking(int x, int y, AbilityStruct* info) {	
	GameMap* map = info->getAbility()->getMap();
	Entity* entity_ = info->getAbility()->getEntity();
	map->getCharacter(Vector2D(x,y))->getComponent<Health>()->hit(1);
	//sdlutils().soundEffects().at("vikingoSound").setChunkVolume(30);
	sdlutils().soundEffects().at("vikingoSound").play(); //-----------------------------------------------------------	
	entity_->getComponent<FramedImage>()->setAnim(A_A_A);
}

Ability_Viking::Ability_Viking() : AbilityStruct(selectorA, ShaderForm::VikingForm, ShaderType::nullSh) 
{
	setAbility([](int x, int y, AbilityStruct* info)
		{
			AbilityViking(x, y, info);
		});
}