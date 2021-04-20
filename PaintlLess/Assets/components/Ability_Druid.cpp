#include "Ability_Druid.h"
#include "Ability_Creeper.h"
#include "../game/PlayState.h"

void Ability_Druid::init() {
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	tex = &sdlutils().images().at("selector");
}

void Ability_Druid::render() {
	SDL_Rect dest;
	for (Vector2D casilla : casillasHabilidad) {
		dest.x = casilla.getX() * cellWidth /*+ offset*/;
		dest.y = casilla.getY() * cellHeight + OFFSET_Y /*+ offset*/;
		dest.h = cellHeight;
		dest.w = cellWidth;
		tex->render(dest);
	}
}

void Ability_Druid::update() {
	auto pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));

			if (esConstruible(posMovimiento)) {
				habilidad = false;
				pos.setX(posMovimiento.getX() * cellWidth);
				pos.setY(posMovimiento.getY() * cellHeight);
				generateWall(posMovimiento.getX(), posMovimiento.getY());
			}
			selected = false;
			freeAbilityShader();

		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight && pSt->getAcciones() > 0 && habilidad) {
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

void Ability_Druid::finTurno()
{
	habilidad = true;
}

void Ability_Druid::AbilityShader() {
	posArc = entity_->getComponent<Transform>()->getPos();
	posArc = mapa->SDLPointToMapCoords(posArc);

	Vector2D posUp = Vector2D(0, -1) + posArc;
	Vector2D posRight = Vector2D(1, 0) + posArc;
	Vector2D posLeft = Vector2D(-1, 0) + posArc;
	Vector2D posDown = Vector2D(0, 1) + posArc;

	if (mapa->movimientoPosibleEnredadera(posUp)) casillasHabilidad.push_back(posUp);
	if (mapa->movimientoPosibleEnredadera(posRight)) casillasHabilidad.push_back(posRight);
	if (mapa->movimientoPosibleEnredadera(posLeft)) casillasHabilidad.push_back(posLeft);
	if (mapa->movimientoPosibleEnredadera(posDown)) casillasHabilidad.push_back(posDown);
}

void Ability_Druid::freeAbilityShader() {
	casillasHabilidad.clear();
}

void Ability_Druid::generateWall(int x, int y) {

	posArc = entity_->getComponent<Transform>()->getPos();

	posArc = mapa->SDLPointToMapCoords(posArc);

	Vector2D posUp = Vector2D(0, -1) + posArc;
	Vector2D posDown = Vector2D(0, 1) + posArc;

	if (Vector2D(x, y) == posUp || Vector2D(x, y) == posDown) {
		for (int i = -1; i < 2; i++) {
			if (mapa->movimientoPosibleEnredadera(Vector2D(x + i, y))) {
				auto* e = entity_->getMngr()->addEntity(RenderLayer::Tablero3);
				e->addComponent<Transform>(
					Vector2D(x + i, y), //Posicion
					Vector2D(),     //Velocidad
					50.0f,          //Ancho
					50.0f,          //Alto
					0.0f);

				e->addComponent<Image>(&sdlutils().images().at("enredadera"));
				e->addComponent<Health>(1);
				e->addComponent<Ability_Creeper>(equip);
				mapa->setObstaculo(Vector2D(x + i, y), e);
				if (equip == 0) e->setGroup<Equipo_Rojo>(e);
				else e->setGroup<Equipo_Azul>(e);
			}
		}
	}
	else
		for (int i = -1; i < 2; i++) {
			if (mapa->movimientoPosibleEnredadera(Vector2D(x, y + i))) {
				auto* e = entity_->getMngr()->addEntity(RenderLayer::Tablero3);
				e->addComponent<Transform>(
					Vector2D(x, y + i), //Posicion
					Vector2D(),     //Velocidad
					50.0f,          //Ancho
					50.0f,          //Alto
					0.0f);

				e->addComponent<Image>(&sdlutils().images().at("enredadera"));
				e->addComponent<Health>(1);
				e->addComponent<Ability_Creeper>(equip);
				mapa->setObstaculo(Vector2D(x, y + i), e);
				if (equip == 0) e->setGroup<Equipo_Rojo>(e);
				else e->setGroup<Equipo_Azul>(e);
			}
		}
}


bool Ability_Druid::esConstruible(const Vector2D& cas) {
	bool esPosible = false;
	int i = 0;
	while (!esPosible && i < casillasHabilidad.size()) {
		if (cas == casillasHabilidad[i])esPosible = true;
		i++;
	}
	return esPosible;
}