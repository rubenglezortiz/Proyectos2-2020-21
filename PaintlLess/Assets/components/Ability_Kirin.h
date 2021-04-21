#pragma once

#include "./Ability.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Movimiento.h"

class Ability_Kirin : public Ability {
public:
	Ability_Kirin() : Ability(selector, nullptr) {}
	virtual ~Ability_Kirin() {}

	void update() override;

private:
	Vector2D posKir;
};
