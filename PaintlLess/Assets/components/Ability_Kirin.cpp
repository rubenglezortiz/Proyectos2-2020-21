#include "Ability_Kirin.h"


void Ability_Kirin::update() {
	auto& pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = map->SDLPointToMapCoords(Vector2D(mX, mY));

			if (abilityCheck(posMovimiento))
			{
				map->removeCharacter(map->SDLPointToMapCoords(pos));
				pos.setX(posMovimiento.getX() * cellWidth);
				pos.setY(posMovimiento.getY() * cellHeight);
				map->setCharacter(map->SDLPointToMapCoords(pos), entity_);
			}
			map->setColor(map->SDLPointToMapCoords(pos), Amarillo);
			selected = false;
			freeAbilityShader();
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			selected = true;
			AbilityShader(Cross, KirinSh, 2);
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeAbilityShader();
	}
}