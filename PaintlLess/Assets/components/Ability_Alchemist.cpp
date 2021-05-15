#include "Ability_Alchemist.h"

void Ability_Alchemist::AbilityExecute(int x, int y)
{
	if (map->getCharacter(Vector2D(x, y))->hasComponent<Movimiento>()) {
		entity_->getComponent<FramedImage>()->setAnim(A_A_A);
		map->getCharacter(Vector2D(x, y))->getComponent<Movimiento>()->setStun(2);
		sdlutils().soundEffects().at("alquimistaSound").play(); //-----------------------------------------------------------	
	}	
	//sdlutils().soundEffects().at("alquimistaSound").setChunkVolume(30);	
}