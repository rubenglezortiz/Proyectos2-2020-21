#include "Attack.h"
#include "../game/PlayState.h"

void Attack::init() {
	tr_ = entity_->getComponent<Transform>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	tex_ = &sdlutils().images().at("selectorA");
}

void Attack::update() {
	if ((entity_->hasGroup<Equipo_Azul>() && playState->getTurno() == Primero ||
		entity_->hasGroup<Equipo_Rojo>() && playState->getTurno() == Segundo) && entity_->getComponent<Movimiento>()->getStun() == 0) {

		attack();
	}
}

void Attack::finTurno()
{
	casillasAtaque.clear();
	ability_usable = true;
}

void Attack::attack() {
	auto& pos = tr_->getPos();

	if (ih().getMouseButtonState(ih().LEFT) ) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected ) {
			//esto se debe hacer en movementshader
			Vector2D cas = mapa->SDLPointToMapCoords(Vector2D(mX, mY));
			// Se tendría que hacer diferenciación entre el equipo del personaje.
			if (canAttack(cas)) {
				if (entity_->getComponent<Ability_Rogue>() != nullptr)
					mapa->getCharacter(cas)->getComponent<Health>()->hit(entity_->getComponent<Ability_Rogue>()->ataqueCritico());								
				else {
					auto* mCha = mapa->getCharacter(cas);
					if(mCha != nullptr)
						mapa->getCharacter(cas)->getComponent<Health>()->hit(1);
					auto* mObs = mapa->getObstaculo(cas);
					if(mObs != nullptr)
						mapa->getObstaculo(cas)->getComponent<Health>()->hit(1);
				}				
				sdlutils().soundEffects().at(sound).setChunkVolume(15);
				sdlutils().soundEffects().at(sound).play(); //-----------------------------------------------------------			
				ability_usable = false;
				playState->aumentarAcciones(); //en realidad se restan acciones 
			}
			selected = false;
			casillasAtaque.clear();
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight && playState->getAcciones() > 0 && ability_usable) {
			selected = true;
			attackShader();
		}
	}
	if (ih().getMouseButtonState(ih().RIGHT)) {
		selected = false;
		casillasAtaque.clear();
	}
}

void Attack::attackShader() {
	Vector2D pos = tr_->getPos();

	pos = mapa->SDLPointToMapCoords(pos);

	for (int i = 1; i <= range; ++i) {
		Vector2D posUp = Vector2D(0, i) + pos;
		Vector2D posRight = Vector2D(i, 0) + pos;
		Vector2D posLeft = Vector2D(-i, 0) + pos;
		Vector2D posDown = Vector2D(0, -i) + pos;
		if (mapa->ataquePosible(posUp))
			casillasAtaque.push_back(posUp);
		if (mapa->ataquePosible(posRight))
			casillasAtaque.push_back(posRight);
		if (mapa->ataquePosible(posLeft))
			casillasAtaque.push_back(posLeft);
		if (mapa->ataquePosible(posDown))
			casillasAtaque.push_back(posDown);
	}
}

void Attack::render() {
	SDL_Rect dest;
	for (Vector2D casilla : casillasAtaque) {
		dest.x = casilla.getX() * cellWidth + OFFSET_X;
		dest.y = casilla.getY() * cellHeight + OFFSET_Y + OFFSET_TOP;
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