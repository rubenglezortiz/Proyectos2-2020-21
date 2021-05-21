#pragma once

#include "./Ability.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Movimiento.h"

struct Ability_Kirin : public AbilityStruct {
public:
	Ability_Kirin() : AbilityStruct(selector, ShaderForm::Cross, ShaderType::KirinSh) { ; }
	virtual ~Ability_Kirin() {}
	virtual void AbilityExecute(int x, int y);
	void finTurno() override { self->ability_usable = true; self->freeAbilityShader(); }
};