#include "Ability_Viking.h"


void Ability_Viking::init() {
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	tex = &sdlutils().images().at("selectorA");
}

void Ability_Viking::update() {
	auto pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));

			if (!casillasHabilidad.empty() && posMovimiento == casillasHabilidad.back()) {
				pos.setX(posMovimiento.getX() * cellWidth);
				pos.setY(posMovimiento.getY() * cellHeight);
				mapa->getCharacter(posMovimiento)->getComponent<Health>()->hit(1);
				//ANIMACI�N HACHA
			}
			selected = false;
			freeAbilityShader();

		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			//si la casilla est� fuera del mapa no hago nada
			//if (nextPos.getX() < 0 || nextPos.getX() >= mapa->getColumns() ||
			//	nextPos.getY() < 0 || nextPos.getY() >= mapa->getRows()) return;
			selected = true;
			AbilityShader();
			//movShader->casillasPosiblesRecu(mov->SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY())), casillasChecked);
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeAbilityShader();
	}
}

void Ability_Viking::render() {
	SDL_Rect dest;

	for (int i = 0; i < casillasHabilidad.size(); ++i) {
		dest.x = casillasHabilidad[i].getX() * cellWidth /*+ offset*/;
		dest.y = casillasHabilidad[i].getY() * cellHeight /*+ offset*/;
		dest.h = cellHeight;
		dest.w = cellWidth;
		if (i < casillasHabilidad.size() - 1)
			tex->render(dest);
	}
	auto tex_fin = &sdlutils().images().at("selector");
	tex_fin->render(dest);
	if (size < 1) size += 0.1;
	int cas = 0;

	for (Vector2D casilla : casillasHabilidad) {
		if (cas == casillasHabilidad.size()) return;
		dest.x = casilla.getX() * cellWidth  /*+ offset*/;
		dest.y = casilla.getY() * cellHeight /*+ offset*/;
		dest.h = cellHeight * size;
		dest.w = cellWidth * size;

		tex->render(dest);
		cas++;
	}
}

void Ability_Viking::AbilityShader() {
	posVik = mapa->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos()) + Vector2D(1, 0);
	bool findObj = false;
	while (!findObj && mapa->casillaValida(posVik)) {
		if (mapa->ataquePosible(posVik))
			findObj = true;
		casillasHabilidad.push_back(posVik);
		posVik = posVik + Vector2D(1, 0);
	}
	// Si no encuentra objetivo.
	if (!findObj)freeAbilityShader();
}

void Ability_Viking::freeAbilityShader() {
	casillasHabilidad.clear();
}