#include "Ability_Architect.h"
#include "../game/OffsetInfo.h"

void Ability_Architect::init() {
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	mov = entity_->getComponent<Movimiento>();
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	tex = &sdlutils().images().at("selector");
}

void Ability_Architect::render() {
	SDL_Rect dest;
	for (Vector2D casilla : casillasHabilidad) {
		dest.x = casilla.getX() * cellWidth /*+ offset*/;
		dest.y = casilla.getY() * cellHeight  + OFFSET_Y/*+ offset*/;
		dest.h = cellHeight;
		dest.w = cellWidth;
		tex->render(dest);
	}
}

void Ability_Architect::update() {
	auto pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));

			if (esConstruible(posMovimiento)) {
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
			AbilityShader();
			//movShader->casillasPosiblesRecu(mov->SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY())), casillasChecked);
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeAbilityShader();
	}
}

void Ability_Architect::AbilityShader() {
	posArc = entity_->getComponent<Transform>()->getPos();

	posArc = mapa->SDLPointToMapCoords(posArc);

	Vector2D posUp = Vector2D(0, 1) + posArc;
	Vector2D posRight = Vector2D(1, 0) + posArc;
	Vector2D posLeft = Vector2D(-1, 0) + posArc;
	Vector2D posDown = Vector2D(0, -1) + posArc;

	if (mapa->movimientoPosible(posUp)) casillasHabilidad.push_back(posUp);
	if (mapa->movimientoPosible(posRight)) casillasHabilidad.push_back(posRight);
	if (mapa->movimientoPosible(posLeft)) casillasHabilidad.push_back(posLeft);
	if (mapa->movimientoPosible(posDown)) casillasHabilidad.push_back(posDown);
}

void Ability_Architect::freeAbilityShader() {
	casillasHabilidad.clear();
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
	mapa->setCharacter(Vector2D(x, y), e);
}

bool Ability_Architect::esConstruible(const Vector2D& cas) {
	bool esPosible = false;
	int i = 0;
	while (!esPosible && i < casillasHabilidad.size()) {
		if (cas == casillasHabilidad[i])esPosible = true;
		i++;
	}
	return esPosible;
}