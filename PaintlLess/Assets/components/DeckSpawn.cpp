#include "DeckSpawn.h"
#include "Ability_Architect.h"
#include "Ability_Bomb.h"
#include "Ability_Golem.h"
#include "Ability_Kirin.h"
#include "Ability_Rogue.h"
#include "Ability_Viking.h"
#include "Ability_Druid.h"
#include "GameMap.h"
#include "Image.h"
#include "Movimiento.h"
#include "Health.h"
#include "Attack.h"

void DeckSpawn::init() {
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
}

void DeckSpawn::createCharacter(int character, int equipo) {
	Entity* charac = entity_->getMngr()->addEntity(RenderLayer::Personajes);
	if (equipo == Primero) charac->setGroup<Equipo_Rojo>(charac);
	else charac->setGroup<Equipo_Azul>(charac);
	switch (character) {
	case Alquimista:
		charac->addComponent<Image>(&sdlutils().images().at("alquimista"));
		//auto t = charac->addComponent<Transform>(Vector2D(0, 0), Vector2D(), 50.0f, 50.0f, 0.0f);
		//charac->addComponent<Movimiento>(this);
		// Habilidad Alquimista
		charac->addComponent<Health>(2);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		break;
	case Arquitecta:
		charac->addComponent<Image>(&sdlutils().images().at("arquitecta"));
		//auto t = charac->addComponent<Transform>(Vector2D(0, 1), Vector2D(), 50.0f, 50.0f, 0.0f);
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Ability_Architect>();
		charac->addComponent<Health>(2);
		//charac->addComponent<Attack>(this);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		break;
	case Bomba:
		charac->addComponent<Image>(&sdlutils().images().at("bomba"));
		//auto t = charac->addComponent<Transform>(Vector2D(0, 2), Vector2D(), 50.0f, 50.0f, 0.0f);
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Ability_Bomb>();
		charac->addComponent<Health>(3);
		//charac->addComponent<Attack>(this);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		break;
	case Cazador:
		charac->addComponent<Image>(&sdlutils().images().at("cazador"));
		//auto t = charac->addComponent<Transform>(Vector2D(0, 3), Vector2D(), 50.0f, 50.0f, 0.0f);
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Health>(3);
		//charac->addComponent<Attack>(this, 2);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		break;
	case Druida:	
		//auto t = charac->addComponent<Transform>(Vector2D(0, 4), Vector2D(), 50.0f, 50.0f, 0.0f);
		charac->addComponent<Image>(&sdlutils().images().at("druida"));
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Health>(3);
		//charac->addComponent<Ability_Druid>(this, (int)equipo);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		sdlutils().showCursor();
		break;
	case Esqueleto:
		//auto t = charac->addComponent<Transform>(Vector2D(0, 5), Vector2D(), 50.0f, 50.0f, 0.0f);
		charac->addComponent<Image>(&sdlutils().images().at("esqueleto"));
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Health>(3);
		//charac->addComponent<Attack>(this);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		break;
	case Golem:
		//auto t = charac->addComponent<Transform>(Vector2D(0, 6), Vector2D(), 50.0f, 50.0f, 0.0f);
		charac->addComponent<Image>(&sdlutils().images().at("golem"));
		charac->addComponent<Ability_Golem>();
		charac->addComponent<Health>(3);
		//charac->addComponent<Attack>(this);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		break;
	case Kirin:	
		//auto t = charac->addComponent<Transform>(Vector2D(0, 7), Vector2D(), 50.0f, 50.0f, 0.0f);
		charac->addComponent<Image>(&sdlutils().images().at("monaguillo"));
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Health>(3);
		//charac->addComponent<Attack>(this);
		charac->addComponent<Ability_Kirin>();
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		break;
	case Lobo:
		//auto t = charac->addComponent<Transform>(Vector2D(0, 8), Vector2D(), 50.0f, 50.0f, 0.0f);
		charac->addComponent<Image>(&sdlutils().images().at("lobo"));
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Health>(3);
		//charac->addComponent<Attack>(this);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		sdlutils().showCursor();
		break;
	case Monaguillo:
		//auto t = charac->addComponent<Transform>(Vector2D(2, 0), Vector2D(), 50.0f, 50.0f, 0.0f);
		charac->addComponent<Image>(&sdlutils().images().at("monaguillo"));
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Health>(3);
		//charac->addComponent<Attack>(this);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		break;
	case Picara:
		//auto t = charac->addComponent<Transform>(Vector2D(1, 0), Vector2D(), 50.0f, 50.0f, 0.0f);
		charac->addComponent<Image>(&sdlutils().images().at("picara"));
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Health>(3);
		charac->addComponent<Ability_Rogue>();
		//charac->addComponent<Attack>(this);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		charac->addComponent<Image>(&sdlutils().images().at("picara"));
		break;
	case Tanque:
		if (equipo == Primero) {
			charac->setGroup<Equipo_Rojo>(charac);
			//auto t = charac->addComponent<Transform>(Vector2D(1, 1), Vector2D(), 50.0f, 50.0f, 0.0f);
			//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		}
		else {
			charac->setGroup<Equipo_Azul>(charac);
			//auto t = charac->addComponent<Transform>(Vector2D(8, 1), Vector2D(), 50.0f, 50.0f, 0.0f);
			//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		}
		charac->addComponent<Image>(&sdlutils().images().at("tanque"));
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Health>(3);
		//charac->addComponent<Attack>(this);
		break;
	case Vikingo:
		//auto t = charac->addComponent<Transform>(Vector2D(1, 2), Vector2D(), 50.0f, 50.0f, 0.0f);
		charac->addComponent<Image>(&sdlutils().images().at("vikingo"));
		//charac->addComponent<Movimiento>(this);
		charac->addComponent<Health>(3);
		charac->addComponent<Ability_Viking>();
		//charac->addComponent<Attack>(this);
		//mapa->setCharacter(mapa->SDLPointToMapCoords(t->getPos()), charac);
		break;
	}
}