#include "Ability_Druid.h"
#include "Ability_Creeper.h"
#include "../game/PlayState.h"


void Ability_Druid::finTurno()
{
	ability_usable = true;
	freeAbilityShader();
}

void Ability_Druid::AbilityExecute(int x, int y) {

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
	else {
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
	entity_->getComponent<FramedImage>()->setAnim(A_A_A);
	//sdlutils().soundEffects().at("crearEnredaderasSound").setChunkVolume(40);
	sdlutils().soundEffects().at("crearEnredaderasSound").play(); //-----------------------------------------------------------		
}