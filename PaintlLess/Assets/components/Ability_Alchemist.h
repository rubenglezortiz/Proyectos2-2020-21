#pragma once

#include "Ability.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "./Health.h"
#include "./Movimiento.h"

class Ability_Alchemist : public Ability
{
public:
	Ability_Alchemist() : Ability(selectorA, ShaderForm::Cross, ShaderType::AttackSh) {}
	~Ability_Alchemist() {};

	void AbilityExecute(int x, int y);
};