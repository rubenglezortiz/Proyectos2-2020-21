#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../game/OffsetInfo.h"
#include "Movimiento.h"
#include "Health.h"

class Ability_Wolf : public AbilityStruct {
public:
	Ability_Wolf(): AbilityStruct(selectorA, ShaderForm::ShaderWolf, ShaderType::nullSh) {}
	virtual ~Ability_Wolf() {}
	void AbilityExecute(int x, int y);


};

