#include "Ability_Viking.h"

void Ability_Viking::AbilityExecute(int x, int y)
{
	auto pos = entity_->getComponent<Transform>()->getPos();
	pos.setX(x * cellWidth);
	pos.setY(y* cellHeight);
	map->getCharacter(Vector2D(x,y))->getComponent<Health>()->hit(1);
	sdlutils().soundEffects().at("vikingoSound").setChunkVolume(30);
	sdlutils().soundEffects().at("vikingoSound").play(); //-----------------------------------------------------------	
}