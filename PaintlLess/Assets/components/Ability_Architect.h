#pragma once

#include "./Ability.h"
#include "../sdlutils/InputHandler.h"
#include "../game/OffsetInfo.h"
#include "Movimiento.h"
#include "Health.h"

class Ability_Architect : public Ability {
public:
	Ability_Architect() : Ability(selector, ShaderForm::Cross, ShaderType::DefenseSh), dest(SDL_Rect()),
		posArc(Vector2D()), resultado(0), selected(false) {}
	virtual ~Ability_Architect() {  }

	void AbilityExecute(int x, int y);
	void finTurno() override { ability_usable = true; freeAbilityShader(); }
private:
	SDL_Rect dest;
	Vector2D posArc;
	int resultado;
	bool selected;
	std::vector<Vector2D> casillasHabilidad;

	//cuando se metan margenes hay que tener cuidadd y sumarlos
};
