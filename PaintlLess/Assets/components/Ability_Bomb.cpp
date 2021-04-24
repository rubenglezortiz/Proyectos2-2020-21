#include "Ability_Bomb.h"

void Ability_Bomb::init()
{
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	assert(mapa != nullptr);
}

void Ability_Bomb::explode() {
	Vector2D posBomb = entity_->getComponent<Transform>()->getPos();

	posBomb = mapa->SDLPointToMapCoords(posBomb);


	//FALTA QUE EXPLOTE AL PISAR AREA ENEMIGA -------------------------------------------------------------------------

	for (int i = 0; i < casillas.size(); i++){
		//Hay personajes ==> Da�o
		if (mapa->getCharacter(casillas[i] + posBomb) != nullptr){
			mapa->getCharacter(casillas[i] + posBomb)->getComponent<Health>()->hit(1);
		}
		//Es pintable ==> Pinta
		if (mapa->movimientoPosible(casillas[i] + posBomb)) {
			if(entity_->hasGroup<Equipo_Azul>())
				mapa->setColor(casillas[i] + posBomb, Amarillo);
			else
				mapa->setColor(casillas[i] + posBomb, Rojo);
		} 
	}
}
