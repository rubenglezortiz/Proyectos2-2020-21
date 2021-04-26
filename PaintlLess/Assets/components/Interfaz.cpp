#include "Interfaz.h"
#include "../game/PlayState.h"

void Interfaz::init() {
	playState = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>()->getPlayState();
	texEnergy = &sdlutils().images().at("energia");
	numCasillasPintables = entity_->getComponent<GameMap>()->getNumCasPintables();
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

	destAcciones.x = sdlutils().width()-550;	//BARRA DE ACCION
	destAcciones.y = 5;
	destAcciones.w = 240;
	destAcciones.h = 90;	
	sdlutils().images().at("barraAccion").render(destAcciones);

	destEnergy.x = sdlutils().width() - 520;	//ENERGIA
	destEnergy.y = 35;
	destEnergy.w = 30;
	destEnergy.h = 30;	

	for (int i = 0; i < playState->getAcciones(); ++i)
	{
		texEnergy->render(destEnergy);
		destEnergy.x = destEnergy.x + destEnergy.w + 20;
	}	

	destBarraTurnos.h = 90;					//BARRA DE TURNOS
	destBarraTurnos.w = 720;
	destBarraTurnos.x = sdlutils().width() - 2*destBarraTurnos.w + 125;	
	destBarraTurnos.y = 5;
	sdlutils().images().at("barraTurnos").render(destBarraTurnos);


	destTurnos.x = sdlutils().width()/2 - 335;	//TURNOS
	destTurnos.y = 35;
	destTurnos.w = 29;
	destTurnos.h = 35;

	for (int i = 0; i < playState->getTurnosActuales(); ++i)
	{
		texEnergy->render(destTurnos);
		destTurnos.x = destTurnos.x + destTurnos.w + 5;
	}

	casAzul =  playState->getPintado1() * 100 / numCasillasPintables;
	casRojo =  playState->getPintado2() * 100 / numCasillasPintables;
	
	destPorcentaje1.x = 175;					//PORCENTAJES
	destPorcentaje2.x = 225;
	destPorcentaje1.y = destPorcentaje2.y = 35;
	destPorcentaje1.w = destPorcentaje2.w = 29;
	destPorcentaje1.h = destPorcentaje2.h = 35;

	Texture(sdlutils().renderer(), to_string(casAzul), sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x7ce5fbff)).render(destPorcentaje1);
	Texture(sdlutils().renderer(), to_string(casRojo), sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0xff00dcff)).render(destPorcentaje2);
}