#pragma once
#include "../ecs/Component.h"

class TanqueA : public Component {
public:
	TanqueA(int turnoActual, int maxTurnos, int lastVida) :turnoActual(turnoActual),
		maxTurnos(maxTurnos), lastVida(lastVida) {}
	int turnoActual;
	int maxTurnos;
	int lastVida;
};