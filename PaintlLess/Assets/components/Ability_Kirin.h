#pragma once

#include "./Ability.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Movimiento.h"
#include "../game/AbilityStruct.h"

struct Ability_Kirin : public AbilityStruct {
public:
	Ability_Kirin();
	virtual ~Ability_Kirin() {}
};