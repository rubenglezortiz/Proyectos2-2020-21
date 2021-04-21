#include "Ability_Viking.h"



void Ability_Viking::update() {
	auto pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = map->SDLPointToMapCoords(Vector2D(mX, mY));

			if (!abilityCells.empty() && posMovimiento == abilityCells.back()) {
				pos.setX(posMovimiento.getX() * cellWidth);
				pos.setY(posMovimiento.getY() * cellHeight);
				map->getCharacter(posMovimiento)->getComponent<Health>()->hit(1);
				//ANIMACIÓN HACHA
			}
			selected = false;
			freeAbilityShader();
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {		
			selected = true;
			//if(entity_->get)
			AbilityShader(VikingForm);			
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeAbilityShader();
	}
}