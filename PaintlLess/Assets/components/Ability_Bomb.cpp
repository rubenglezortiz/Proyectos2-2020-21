#include "Ability_Bomb.h"

void Ability_Bomb::init()
{
	tr = entity_->getComponent<Transform>();
	assert(tr != nullptr);
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	assert(mapa != nullptr);
}

void Ability_Bomb::explode() {
	posBomb = entity_->getComponent<Transform>()->getPos();

	posBomb = mapa->SDLPointToMapCoords(posBomb);

	//Casillas 3x3
	Vector2D posUp = Vector2D(0, -1) + posBomb;
	casillas.push_back(posUp);
	Vector2D posUpLeft = Vector2D(-1, -1) + posBomb;
	casillas.push_back(posUpLeft);
	Vector2D posUpRight = Vector2D(1, -1) + posBomb;
	casillas.push_back(posUpRight);
	Vector2D posRight = Vector2D(1, 0) + posBomb;
	casillas.push_back(posRight);
	Vector2D posLeft = Vector2D(-1, 0) + posBomb;
	casillas.push_back(posLeft);
	Vector2D posDown = Vector2D(0, 1) + posBomb;
	casillas.push_back(posDown);
	Vector2D posDownLeft = Vector2D(-1, 1) + posBomb;
	casillas.push_back(posDownLeft);
	Vector2D posDownRight = Vector2D(1, 1) + posBomb;
	casillas.push_back(posDownRight);

	//FALTA QUE EXPLOTE AL PISAR AREA ENEMIGA -------------------------------------------------------------------------

	for (int i = 0; i < casillas.size(); i++){
		//Hay personajes ==> Daño
		if (mapa->getCharacter(casillas[i]) != nullptr){
			mapa->getCharacter(casillas[i])->getComponent<Health>()->hit(1);
		}
		//Es pintable ==> Pinta
		if (mapa->movimientoPosible(casillas[i])) mapa->setColor(casillas[i], Amarillo);
	}
}
