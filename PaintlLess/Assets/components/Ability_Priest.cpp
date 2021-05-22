#include "Ability_Priest.h"

void AbilityPriest(int x, int y, AbilityStruct* info) {
	GameMap* map = info->getAbility()->getMap();
	Entity* entity_ = info->getAbility()->getEntity();
	std::vector<Vector2D> abilityCells = info->getAbility()->getCells();
	if (abilityCells.empty())
	{
		info->getAbility()->Shade();
		abilityCells = info->getAbility()->getCells();
	}
	for (int i = 0; i < abilityCells.size(); i++) {
		if (map->getCharacter(abilityCells[i]) != nullptr) {
			if ((map->getCharacter(abilityCells[i])->hasGroup<Equipo_Azul>() && entity_->hasGroup<Equipo_Azul>()) || (map->getCharacter(abilityCells[i])->hasGroup<Equipo_Rojo>() && entity_->hasGroup<Equipo_Rojo>())) {
				map->getCharacter(abilityCells[i])->getComponent<Health>()->healMonaguillo(1);
				entity_->getComponent<FramedImage>()->setAnim(A_A_A);
				sdlutils().soundEffects().at("monaguilloSound").play(); //-----------------------------------------------------------						
				//sdlutils().soundEffects().at("monaguilloSound").setChunkVolume(127);
			}				
		}
	}
}

Ability_Priest::Ability_Priest() : AbilityStruct(selectorH, ShaderForm::TxT, ShaderType::nullSh) 
{
	setAbility([](int x, int y, AbilityStruct* info)
		{
			AbilityPriest(x, y, info);
		});
}
