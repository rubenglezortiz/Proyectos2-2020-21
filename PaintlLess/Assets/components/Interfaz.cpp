#include "Interfaz.h"
#include "../game/PlayState.h"

void Interfaz::init() {
	playState = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>()->getPlayState();
}

void Interfaz::render() {
	int mana;
	if (playState->getCurrentPlayer() == 0) mana = playState->getMana2();
	else mana  = playState->getMana1();
	destNum.x  = sdlutils().width() - 100;
	destMana.x = sdlutils().width() - 225;
	if (mana == 10)
		destNum.w = 100;
	else 
		destNum.w = 70;
	destMana.w = 225;
	destNum.h  = 90; destMana.h = 100;
	destNum.y  = sdlutils().height() - 90;
	destMana.y = sdlutils().height() - 100;
	sdlutils().images().at("mana").render(destMana);
	Texture(sdlutils().renderer(), to_string(mana), sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x7ce5fbff)).render(destNum);
}