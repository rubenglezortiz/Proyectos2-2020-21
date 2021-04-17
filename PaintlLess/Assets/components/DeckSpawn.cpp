#include "DeckSpawn.h"
#include "Ability_Architect.h"
#include "Ability_Bomb.h"
#include "Ability_Druid.h"
#include "Ability_Golem.h"
#include "Ability_Kirin.h"
#include "Ability_Priest.h"
#include "Ability_Rogue.h"
#include "Ability_Viking.h"
#include "Attack.h"
#include "GameMap.h"
#include "Health.h"
#include "Image.h"
#include "Movimiento.h"

void DeckSpawn::init() {
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	tex = &sdlutils().images().at("selectorSp");
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	playState = mapa->getPlayState();
}

void DeckSpawn::health(Entity* c, int l) {
	c->addComponent<Health>(l);
}

void DeckSpawn::movement(Entity* c) {
	c->addComponent<Movimiento>(playState);
}

void DeckSpawn::image(Entity* c, string t) {
	c->addComponent<Image>(&sdlutils().images().at(t));
}

void DeckSpawn::attack(Entity* c, int dmg = 1) {
	c->addComponent<Attack>(playState, dmg);
}

void DeckSpawn::createCharacter(int character, int equipo, Vector2D pos) {
	Entity* ctr = entity_->getMngr()->addEntity(RenderLayer::Personajes);

	ctr->addComponent<Transform>(pos, Vector2D(), 50.0f, 50.0f, 0.0f);

	if (equipo == Primero) ctr->setGroup<Equipo_Rojo>(ctr);
	else ctr->setGroup<Equipo_Azul>(ctr);

	switch (character) {
	case Alquimista:
		image(ctr, "alquimista"); movement(ctr); health(ctr, 2);
		// Habilidad Alquimista.
		break;
	case Arquitecta:
		image(ctr, "arquitecta"); movement(ctr); health(ctr, 2); attack(ctr);
		ctr->addComponent<Ability_Architect>();
		break;
	case Bomba:
		image(ctr, "bomba");      movement(ctr); health(ctr, 3); attack(ctr);
		ctr->addComponent<Ability_Bomb>();
		break;
	case Cazador:
		image(ctr, "cazador");    movement(ctr); health(ctr, 1); attack(ctr, 2);
		break;
	case Druida:	
		image(ctr, "druida");     movement(ctr); health(ctr, 2);
		ctr->addComponent<Ability_Druid>(playState, (int)equipo);
		break;
	case Esqueleto:
		image(ctr, "esqueleto");  movement(ctr); health(ctr, 1); attack(ctr);
		break;
	case Golem:
		image(ctr, "golem");					 health(ctr, 4); attack(ctr);
		break;
	case Kirin:	
		image(ctr, "monaguillo"); movement(ctr); health(ctr, 2); attack(ctr);
		ctr->addComponent<Ability_Kirin>();
		break;
	case Lobo:
		image(ctr, "lobo");		  movement(ctr); health(ctr, 2);
		// Habilidad del lobo.
		break;
	case Monaguillo:
		image(ctr, "monaguillo"); movement(ctr); health(ctr, 1); attack(ctr);
		ctr->addComponent<Ability_Priest>();
		break;
	case Picara:
		image(ctr, "picara");	  movement(ctr); health(ctr, 2); attack(ctr);
		ctr->addComponent<Ability_Rogue>();
		break;
	case Tanque:
		image(ctr, "tanque");     movement(ctr); health(ctr, 4); attack(ctr);
		break;
	case Vikingo:
		image(ctr, "vikingo");    movement(ctr); health(ctr, 1); attack(ctr);
		ctr->addComponent<Ability_Viking>();
		break;
	}
	mapa->setCharacter(mapa->SDLPointToMapCoords(ctr->getComponent<Transform>()->getPos()), ctr);
}

void DeckSpawn::spawnShader(int e) {
	int k = 0;
	int l = 2;
	if (e == Primero) {
		k = mapa->getColumns() - 2;
		l = mapa->getColumns();
	}
	for (int i = k; i < l; ++i) {
		for (int j = 0; j < mapa->getColumns(); ++j) {
			Vector2D cas = Vector2D(i, j);
			if (mapa->casillaValida(cas))
				if (mapa->getTipoCasilla(cas) == Pintable || mapa->getTipoCasilla(cas) == Base)
					if (mapa->getCharacter(cas) == nullptr && mapa->getObstaculo(cas) == nullptr)
						casillasSpawn.push_back(cas);
		}
	}
}

void DeckSpawn::render() {
	SDL_Rect dest;
	for (Vector2D casilla : casillasSpawn) {
		dest.x = casilla.getX() * cellWidth/*+ offset*/;
		dest.y = casilla.getY() * cellHeight /*+ offset*/;
		dest.h = cellHeight;
		dest.w = cellWidth;
		tex->render(dest);
	}
}

bool DeckSpawn::spawneableCell(Vector2D p) {
	int i = 0;
	bool encontrado = false;
	while (i < casillasSpawn.size() && !encontrado) {
		if (casillasSpawn[i] == p) encontrado = true;
		else i++;
	}
	return encontrado;
}

void DeckSpawn::update() {
	auto pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));
			if (spawneableCell(posMovimiento) && playState->getCurrentPlayer() == 1) createCharacter(personaje, 0, posMovimiento);
			else if (playState->getCurrentPlayer() == 0) createCharacter(personaje, 1, posMovimiento);
			else cout << "Esa casilla no figura en los spawns.";
			selected = false;
			freeShader();
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			selected = true;
			spawnShader(playState->getCurrentPlayer());
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeShader();
	}
}

void DeckSpawn::freeShader() {
	casillasSpawn.clear();
}