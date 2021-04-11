#include "Attack.h"

void Attack::update() {
	attack();
}

void Attack::attack() {
	auto& pos = tr_->getPos();

	if (ih().getMouseButtonState(ih().LEFT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D cas = mapa->SDLPointToMapCoords(Vector2D(mX, mY));
			// Se tendría que hacer diferenciación entre el equipo del personaje.
			if (canAttack(cas)) {
				if (entity_->getComponent<Ability_Rogue>() != nullptr)
					mapa->getCharacter(cas)->getComponent<Health>()->hit(entity_->getComponent<Ability_Rogue>()->ataqueCritico());
				else
					mapa->getCharacter(cas)->getComponent<Health>()->hit(1);
			}
			selected = false;
			casillasAtaque.clear();
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			selected = true;
			attackShader();
		}
	}
	if (ih().getMouseButtonState(ih().RIGHT)) {
		selected = false;
	}
}

void Attack::attackShader() {
	Vector2D pos = tr_->getPos();

	pos = mapa->SDLPointToMapCoords(pos);

	Vector2D posUp = Vector2D(0, 1) + pos;
	Vector2D posRight = Vector2D(1, 0) + pos;
	Vector2D posLeft = Vector2D(-1, 0) + pos;
	Vector2D posDown = Vector2D(0, -1) + pos;

	if (mapa->ataquePosible(posUp))
		casillasAtaque.push_back(posUp);
	if (mapa->ataquePosible(posRight))
		casillasAtaque.push_back(posRight);
	if (mapa->ataquePosible(posLeft))
		casillasAtaque.push_back(posLeft);
	if (mapa->ataquePosible(posDown))
		casillasAtaque.push_back(posDown);
}

void Attack::render() {
	SDL_Rect dest;
	for (Vector2D casilla : casillasAtaque) {
		dest.x = casilla.getX() * cellWidth /*+ offset*/;
		dest.y = casilla.getY() * cellHeight /*+ offset*/;
		dest.h = cellHeight;
		dest.w = cellWidth;

		tex_->render(dest);
	}
}

bool Attack::canAttack(Vector2D cas) {
	bool esPosible = false;
	int i = 0;
	while (!esPosible && i < casillasAtaque.size()) {
		if (cas == casillasAtaque[i])esPosible = true;
		i++;
	}
	return esPosible;
}