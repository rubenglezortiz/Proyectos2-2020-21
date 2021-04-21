#include "Ability_Priest.h"

void Ability_Priest::update() {
	auto pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			heal();
			freeAbilityShader();
			selected = false;
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			selected = true;
			AbilityShader(TxT);
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeAbilityShader();
	}
}

void Ability_Priest::heal() {
	for (int i = 0; i < abilityCells.size(); i++) {
		if (map->getCharacter(abilityCells[i]) != nullptr) {
			if ((map->getCharacter(abilityCells[i])->hasGroup<Equipo_Azul>() && entity_->hasGroup<Equipo_Azul>()) || (map->getCharacter(abilityCells[i])->hasGroup<Equipo_Rojo>() && entity_->hasGroup<Equipo_Rojo>()))
				map->getCharacter(abilityCells[i])->getComponent<Health>()->healMonaguillo(1);
		}
	}
}