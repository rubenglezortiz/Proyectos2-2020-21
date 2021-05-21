#pragma once

#include "./Ability.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "../sdlutils/InputHandler.h"
#include "Movimiento.h"
#include "Health.h"
#include "../game/AbilityStruct.h"

class PlayState;
class Ability_Druid : public AbilityStruct {
public:
	Ability_Druid();
	virtual ~Ability_Druid() {}
};
