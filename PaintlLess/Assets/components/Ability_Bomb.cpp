#include "Ability_Bomb.h"


void AbilityBomb(AbilityStruct* info, const std::vector<Vector2D>& casillas) {
	Entity* entity_ = info->getAbility()->getEntity();
	Vector2D posBomb = entity_->getComponent<Transform>()->getPos();
	GameMap* mapa = info->getAbility()->getMap();
	posBomb = mapa->SDLPointToMapCoords(posBomb);
	std::cout << "X: " << posBomb.getX() << " Y: " << posBomb.getY();

	//FALTA QUE EXPLOTE AL PISAR AREA ENEMIGA -------------------------------------------------------------------------
	for (int i = 0; i < casillas.size(); i++){
		//Hay personajes ==> Da�o
		std::cout << "X: " << casillas[i].getX() << " Y: " << casillas[i].getY();
		if (mapa->casillaValida(casillas[i] + posBomb) && mapa->getCharacter(casillas[i] + posBomb) != nullptr){
			mapa->getCharacter(casillas[i] + posBomb)->getComponent<Health>()->hit(1);
		}
		//Es pintable ==> Pinta
		if (mapa->movimientoPosible(casillas[i] + posBomb)) {
			if(entity_->hasGroup<Equipo_Azul>())
				mapa->setColor(casillas[i] + posBomb, Azul);
			else
				mapa->setColor(casillas[i] + posBomb, Rojo);
		} 
	}
	//sdlutils().soundEffects().at("bombaSound").setChunkVolume(50);
	sdlutils().soundEffects().at("bombaSound").play(); //-----------------------------------------------------------		
}

Ability_Bomb::Ability_Bomb()
{
	const std::vector<Vector2D> casillas{ {0, -1}, {-1, -1}, {1, -1}, {1, 0}, {-1, 0}, {0, 1}, {-1, 1}, {1, 1} };
	setAbility([casillas](int x, int y, AbilityStruct* info) {AbilityBomb(info, casillas); });
	setOnDie([casillas](AbilityStruct* info) {
		AbilityBomb(info, casillas);
		});
}
