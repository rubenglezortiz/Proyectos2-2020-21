#pragma once

#include "./Ability.h"
#include "../sdlutils/InputHandler.h"
#include "../game/OffsetInfo.h"
#include "Movimiento.h"
#include "Health.h"
#include "../game/AbilityStruct.h"

struct Ability_Architect : AbilityStruct {
public:
	Ability_Architect();
	
	virtual ~Ability_Architect() {  }
	void AbilityExecute(int x, int y) override;
	AbilityStructFunction* abFunction;
	void finTurno() override { self->ability_usable = true; self->freeAbilityShader(); }
private:
	SDL_Rect dest;
	Vector2D posArc;
	int resultado;
	bool selected;
	std::vector<Vector2D> casillasHabilidad;

	//cuando se metan margenes hay que tener cuidadd y sumarlos
};
