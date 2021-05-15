#include "DeckSpawn.h"
#include "Ability_Alchemist.h"
#include "Ability_Architect.h"
#include "Ability_Bomb.h"
#include "Ability_Druid.h"
#include "Ability_Golem.h"
#include "Ability_Kirin.h"
#include "Ability_Priest.h"
#include "Ability_Rogue.h"
#include "Ability_Tank.h"
#include "Ability_Viking.h"
#include "Ability_Wolf.h"
#include "Attack.h"
#include "FramedImage.h"
#include "GameMap.h"
#include "Health.h"
#include "Transform2.h"
#include "Image.h"
#include "Movimiento.h"
#include "../game/Values.h"

void DeckSpawn::init() {
	tr_ = entity_->getComponent<Transform2>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	tex = &sdlutils().images().at("selectorSp");
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	playState = mapa->getPlayState();
	turno = playState->getTurno();
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

void DeckSpawn::animation(Entity* c, string tex, int d, Unit p) {	
	if(c->hasGroup<Equipo_Azul>())
		c->addComponent<FramedImage>(&sdlutils().images().at(tex+"R"), d, p);
	else	
		c->addComponent<FramedImage>(&sdlutils().images().at(tex+"A"), d, p);
}

void DeckSpawn::attack(Entity* c, int dmg = 1, string s = "ataqueSound") {
	c->addComponent<Attack>(playState, dmg, s);
}

void DeckSpawn::createCharacter(int character, int equipo, Vector2D pos) {
	Entity* ctr = entity_->getMngr()->addEntity(RenderLayer::Personajes);

	ctr->addComponent<Transform>(pos, Vector2D(), 50.0f, 50.0f, 0.0f);
	ctr->setGroup<Personajes>(ctr);
	if (equipo == Primero) ctr->setGroup<Equipo_Rojo>(ctr);
	else ctr->setGroup<Equipo_Azul>(ctr);

	switch (character) {
	case Alquimista:
		animation(ctr, "alquimistaSheet", 150, Alquimista);	 movement(ctr); health(ctr, 2);
		ctr->addComponent<Ability_Alchemist>();
		break;
	case Arquitecta:
		animation(ctr, "arquitectaSheet", 150, Arquitecta);	 movement(ctr); health(ctr, 2);
		ctr->addComponent<Ability_Architect>();
		break;
	case Bomba:
		animation(ctr, "bombaSheet", 150, Bomba);   movement(ctr); health(ctr, 3); 
		ctr->addComponent<Ability_Bomb>();
		break;
	case Cazador:
		image(ctr, "cazador");  movement(ctr); health(ctr, 1); attack(ctr, 2, "arqueroSound");
		break;
	case Druida:
		animation(ctr, "druidaSheet", 125, Druida);   movement(ctr); health(ctr, 2);
		ctr->addComponent<Ability_Druid>(playState, (int)equipo);
		break;
	case Esqueleto:
		animation(ctr, "esqueletoSheet", 150, Esqueleto);  movement(ctr); health(ctr, 1); attack(ctr);
		break;
	case Golem:
		animation(ctr, "golemSheet", 120, Golem);	health(ctr, 4); attack(ctr); ctr->addComponent<Movimiento>(playState, 0);
		ctr->addComponent<Ability_Golem>();
		break;
	case Kirin:
		animation(ctr, "kirinSheet", 150, Kirin);	movement(ctr); health(ctr, 2); attack(ctr);
		ctr->addComponent<Ability_Kirin>();
		break;
	case Lobo:
		animation(ctr, "loboSheet", 150, Lobo);	  movement(ctr); health(ctr, 2);
		ctr->addComponent<Ability_Wolf>();
		break;
	case Monaguillo:
		animation(ctr, "monaguilloSheet", 150, Monaguillo); movement(ctr); health(ctr, 1); attack(ctr);
		ctr->addComponent<Ability_Priest>();
		break;
	case Picara:
		animation(ctr, "picaraSheet", 150, Picara);	  movement(ctr); health(ctr, 2); attack(ctr);
		ctr->addComponent<Ability_Rogue>();
		break;
	case Tanque:
		animation(ctr, "tanqueSheet", 150, Tanque);    movement(ctr); health(ctr, 4); attack(ctr);
		ctr->addComponent<Ability_Tank>();
		break;
	case Vikingo:
		animation(ctr, "vikingoSheet", 150,  Vikingo);  movement(ctr); health(ctr, 1);
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
	if (personaje == 6) {
		if (e == Primero) k -= 2;
		else l += 2;
	}
	for (int i = k; i < l; ++i) {
		for (int j = 0; j < mapa->getColumns(); ++j) {
			Vector2D cas = Vector2D(i, j);
			if (mapa->casillaValida(cas))
				if (mapa->getTipoCasilla(cas) == Base || (turno == Primero && mapa->getColor(cas) == Amarillo) || (turno == Segundo && mapa->getColor(cas) == Rojo))
					if (mapa->getCharacter(cas) == nullptr && mapa->getObstaculo(cas) == nullptr)
						casillasSpawn.push_back(cas);
		}
	}
}

void DeckSpawn::render() {
	SDL_Rect dest;
	for (Vector2D casilla : casillasSpawn) {
		dest.x = casilla.getX() * cellWidth + OFFSET_X;
		dest.y = casilla.getY() * cellHeight + OFFSET_Y + OFFSET_TOP;
		dest.h = cellHeight;
		dest.w = cellWidth;
		tex->render(dest);
	}
	dest.x = tr_->getPos().getX();
	dest.y = tr_->getPos().getY();
	dest.h = tr_->getH();
	dest.w = tr_->getW();

	if (playState->getCurrentPlayer() == 1 && cool1 > 0)
		sdlutils().images().at("cold" + to_string(cool1)).render(dest);
	else if (playState->getCurrentPlayer() == 0 && cool0 > 0)
		sdlutils().images().at("cold" + to_string(cool0)).render(dest);
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
	auto pos = entity_->getComponent<Transform2>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {

		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));
			if (spawneableCell(posMovimiento) && playState->getCurrentPlayer() == 1 && playState->restaMana(UnitInfo::mana[personaje], playState->getMana1())) {
				createCharacter(personaje, 0, posMovimiento);
				cool1 += UnitInfo::cooldown[personaje];
			}
			else if (spawneableCell(posMovimiento) && playState->getCurrentPlayer() == 0 && playState->restaMana(UnitInfo::mana[personaje], playState->getMana2())) {
				createCharacter(personaje, 1, posMovimiento);
				cool0 += UnitInfo::cooldown[personaje];
			}
			else cout << "Esa casilla no figura en los spawns.";
			selected = false;
			freeShader();
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			if (isSpawnable()) {
				selected = true;
				spawnShader(playState->getCurrentPlayer());
				sdlutils().soundEffects().at("seleccionSound").play();
			}
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeShader();
	}
	if (turno != playState->getTurno()) {
		selected = false;
		freeShader();
		turno = playState->getTurno();
	}
}

void DeckSpawn::freeShader() {
	casillasSpawn.clear();
}

void DeckSpawn::finTurno() {
	if (cool0 > 0 && playState->getCurrentPlayer() == 0) cool0--;
	if (cool1 > 0 && playState->getCurrentPlayer() == 1) cool1--;
}

bool DeckSpawn::isSpawnable() const {
	return
		playState->getCurrentPlayer() == 1 &&
		playState->manaSuficiente(UnitInfo::mana[personaje], playState->getMana1()) && cool1 == 0
		||
		playState->getCurrentPlayer() == 0 &&
		playState->manaSuficiente(UnitInfo::mana[personaje], playState->getMana2()) && cool0 == 0;
}