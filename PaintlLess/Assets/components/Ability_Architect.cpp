#include "Ability_Architect.h"


Ability_Architect::Ability_Architect() : Ability([this](int x, int y) {generateWall;}) {
	dest = SDL_Rect();
	posArc = Vector2D();
	resultado = 0;
	selected = false;
}




void Ability_Architect::update() {
	auto pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = map->SDLPointToMapCoords(Vector2D(mX, mY));

			if (abilityCheck(posMovimiento)) {
				pos.setX(posMovimiento.getX() * cellWidth);
				pos.setY(posMovimiento.getY() * cellHeight);
				generateWall(posMovimiento.getX(), posMovimiento.getY());
			}
			selected = false;
			freeAbilityShader();

		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			//si la casilla está fuera del mapa no hago nada
			//if (nextPos.getX() < 0 || nextPos.getX() >= mapa->getColumns() ||
			//	nextPos.getY() < 0 || nextPos.getY() >= mapa->getRows()) return;
			selected = true;
			AbilityShader(DefenseSh,Cross);
			//movShader->casillasPosiblesRecu(mov->SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY())), casillasChecked);
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeAbilityShader();
	}
}

void Ability_Architect::generateWall(int x, int y) {
	// x e y
	//Crea imagen
	auto* e = entity_->getMngr()->addEntity(RenderLayer::Tablero3);

	e->addComponent<Transform>(
		Vector2D(x, y), //Posicion
		Vector2D(),     //Velocidad
		50.0f,          //Ancho
		50.0f,          //Alto
		0.0f);

	e->addComponent<Image>(&sdlutils().images().at("wall"));
	e->addComponent<Health>(2);
	map->setCharacter(Vector2D(x, y), e);
}