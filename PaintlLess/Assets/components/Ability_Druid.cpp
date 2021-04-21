#include "Ability_Druid.h"
#include "Ability_Creeper.h"
#include "../game/PlayState.h"

void Ability_Druid::update() {
	auto pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = map->SDLPointToMapCoords(Vector2D(mX, mY));

			if (abilityCheck(posMovimiento)) {
				habilidad = false;
				pos.setX(posMovimiento.getX() * cellWidth);
				pos.setY(posMovimiento.getY() * cellHeight);
				generateCreeper(posMovimiento.getX(), posMovimiento.getY());
			}
			selected = false;
			freeAbilityShader();

		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight && pSt->getAcciones() > 0 && habilidad) {
			//si la casilla está fuera del mapa no hago nada
			//if (nextPos.getX() < 0 || nextPos.getX() >= mapa->getColumns() ||
			//	nextPos.getY() < 0 || nextPos.getY() >= mapa->getRows()) return;
			selected = true;
			AbilityShader(Cross, DefenseSh);
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

void Ability_Druid::generateCreeper(int x, int y) {

	posDruid = entity_->getComponent<Transform>()->getPos();

	posDruid = map->SDLPointToMapCoords(posDruid);

	Vector2D posUp = Vector2D(0, -1) + posDruid;
	Vector2D posDown = Vector2D(0, 1) + posDruid;

	if (Vector2D(x, y) == posUp || Vector2D(x, y) == posDown) {
		for (int i = -1; i < 2; i++) {
			if (map->movimientoPosibleEnredadera(Vector2D(x + i, y))) {
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
				map->setObstaculo(Vector2D(x + i, y), e);
				if (equip == 0) e->setGroup<Equipo_Rojo>(e);
				else e->setGroup<Equipo_Azul>(e);
			}
		}
	}
	else
		for (int i = -1; i < 2; i++) {
			if (map->movimientoPosibleEnredadera(Vector2D(x, y + i))) {
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
				map->setObstaculo(Vector2D(x, y + i), e);
				if (equip == 0) e->setGroup<Equipo_Rojo>(e);
				else e->setGroup<Equipo_Azul>(e);
			}
		}
}

