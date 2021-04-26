#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform2.h"
#include "Image.h"

class PlayState;

class Interfaz : public Component {
private:
	PlayState* playState;
	SDL_Rect destNum, destMana, destAcciones, destEnergy, destBarraTurnos, destTurnos, destBarraPorcentajes, destPorcentaje1, destPorcentaje2, destOpciones;
	Texture* texEnergy;
	int numCasillasPintables, casAzul, casRojo;
public:
	Interfaz(){}
	virtual ~Interfaz(){}
	void init() override;
	void render() override;
};