#include "Interfaz.h"
#include "../game/PlayState.h"

void Interfaz::init() {
	playState = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>()->getPlayState();
	texEnergy = &sdlutils().images().at("energia");
	texTurno = &sdlutils().images().at("turno");
	numCasillasPintables = entity_->getComponent<GameMap>()->getNumCasPintables();
}

void Interfaz::render() {
	int mana;
	if (playState->getCurrentPlayer() == 0) mana = playState->getMana2();
	else mana  = playState->getMana1();
	destNum.x  = sdlutils().width() - 210;
	destMana.x = sdlutils().width() - 330;
	if (mana == 10)
		destNum.w = 100;
	else 
		destNum.w = 70;
	destMana.w = 225;
	destNum.h  = 90; destMana.h = 100;
	destNum.y  = sdlutils().height() - 110;
	destMana.y = sdlutils().height() - 120;
	sdlutils().images().at("mana").render(destMana);
	Texture(sdlutils().renderer(), to_string(mana), sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0x7ce5fbff)).render(destNum);	

	destAcciones.x = sdlutils().width()-550 + 40;	//BARRA DE ACCION
	destAcciones.y = 25;
	destAcciones.w = 240;
	destAcciones.h = 45;
	sdlutils().images().at("barraAccion").render(destAcciones);

	destEnergy.x = sdlutils().width() - 520 + 40;	//ENERGIA
	destEnergy.y = 33;
	destEnergy.w = 30;
	destEnergy.h = 29;	

	for (int i = 0; i < playState->getAcciones(); ++i){
		texEnergy->render(destEnergy);
		destEnergy.x = destEnergy.x + destEnergy.w + 20;
	}	

	int turnos = playState->getTurnosActuales();
	destNumTurnos.x = (sdlutils().width() / 2) - 270;
	destNumTurnos.y = 35;
	if (turnos < 10) destNumTurnos.w = 30;
	else {
		destNumTurnos.x -= 30;
		destNumTurnos.w = 60;
	}
	destNumTurnos.h = 30;
	Texture(sdlutils().renderer(), to_string(turnos), sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0xfff0bcff)).render(destNumTurnos);
	
	destNumTurnos.x = (sdlutils().width() / 2) - 235;
	destNumTurnos.w = 95;
	Texture(sdlutils().renderer(), "/20", sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0xfff0bcff)).render(destNumTurnos);

	
	destBarraTurnos.h = 45;					//BARRA DE TURNOS
	destBarraTurnos.w = 520;
	destBarraTurnos.x = sdlutils().width() / 2 - 125;
	destBarraTurnos.y = 25;
	sdlutils().images().at("barraTurnos").render(destBarraTurnos);

	destAcciones.x -= 15;
	destAcciones.y -= 10;
	destAcciones.w = 45;
	destAcciones.h = 65;
	sdlutils().images().at("energia1").render(destAcciones);

	destTurnos.x = sdlutils().width() / 2 - 113;	//TURNOS
	destTurnos.y = 37;
	destTurnos.w = 20;
	destTurnos.h = 20;

	for (int i = 0; i < playState->getTurnosActuales(); ++i)
	{
		texTurno->render(destTurnos);
		destTurnos.x = destTurnos.x + destTurnos.w + 5;
	}


	destBarraPorcentajes.x = 145 + 30;
	destBarraPorcentajes.y = 25;
	destBarraPorcentajes.w = 435;
	destBarraPorcentajes.h = 45;
	sdlutils().images().at("barraPorcentajes").render(destBarraPorcentajes);

	destPorcentaje.x = 376;
	destPorcentaje.y = 37;
	destPorcentaje.w = 25;
	destPorcentaje.h = 25;
	sdlutils().images().at("porcentaje").render(destPorcentaje);

	destPorcentaje1.x = 560 + 30;				
	destPorcentaje2.x = 165 + 30;
	destPorcentaje1.y = destPorcentaje2.y = 38;
	destPorcentaje1.w = destPorcentaje2.w = 0;
	destPorcentaje1.h = destPorcentaje2.h = 20;
	
	int off = (destBarraPorcentajes.w - 40) / numCasillasPintables;
	destPorcentaje2.w += playState->getPintado2() * off;
	sdlutils().images().at("porcAzul").render(destPorcentaje2);

	destPorcentaje1.x -= playState->getPintado1() * off;
	destPorcentaje1.w += playState->getPintado1() * off;
	sdlutils().images().at("porcRojo").render(destPorcentaje1);

	destOpciones.x = sdlutils().width() - 275 + 40;
	destOpciones.y = 10;
	destOpciones.w = 78;
	destOpciones.h = 78;
	sdlutils().images().at("opciones").render(destOpciones);

	casRojo = playState->getPintado1() * 100 / numCasillasPintables;
	casAzul = playState->getPintado2() * 100 / numCasillasPintables;

	numPorcA.y = numPorcR.y = 32;
	numPorcA.h = numPorcR.h = 35;
	if (casAzul >= 10) {
		numPorcA.w = 70;
		numPorcA.x = 105;
	}
	else {
		numPorcA.w = 35;
		numPorcA.x = 140;
	}
	if (casRojo >= 10) {
		numPorcR.w = 70;
	}
	else {
		numPorcR.w = 35;
		numPorcR.x = 614;
	}
	Texture(sdlutils().renderer(), to_string(casAzul), sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0x7ce5fbff)).render(numPorcA);
	Texture(sdlutils().renderer(), to_string(casRojo), sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0xff00dcff)).render(numPorcR);
}