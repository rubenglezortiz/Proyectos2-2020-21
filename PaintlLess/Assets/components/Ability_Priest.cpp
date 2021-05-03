#include "Ability_Priest.h"

void Ability_Priest::AbilityExecute(int x, int y) {
	for (int i = 0; i < abilityCells.size(); i++) {
		if (map->getCharacter(abilityCells[i]) != nullptr) {
			if ((map->getCharacter(abilityCells[i])->hasGroup<Equipo_Azul>() && entity_->hasGroup<Equipo_Azul>()) || (map->getCharacter(abilityCells[i])->hasGroup<Equipo_Rojo>() && entity_->hasGroup<Equipo_Rojo>())) {
				map->getCharacter(abilityCells[i])->getComponent<Health>()->healMonaguillo(1);
				sdlutils().soundEffects().at("monaguilloSound").play(); //-----------------------------------------------------------						
				//sdlutils().soundEffects().at("monaguilloSound").setChunkVolume(127);
			}				
		}
	}
}