#pragma once

#include "./Ability.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Movimiento.h"

class Ability_Kirin : public Ability {
public:
	Ability_Kirin() : Ability(selector, ShaderForm::Cross, ShaderType::KirinSh) { SetShaderDistance(2); }
	virtual ~Ability_Kirin() {}
	virtual void AbilityExecute(int x, int y);
};
