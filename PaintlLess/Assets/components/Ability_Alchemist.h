#pragma once

#include "Ability.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "./Health.h"
#include "./Movimiento.h"

struct Ability_Alchemist : public AbilityStruct
{
public:
	Ability_Alchemist();
	virtual ~Ability_Alchemist() {};
};