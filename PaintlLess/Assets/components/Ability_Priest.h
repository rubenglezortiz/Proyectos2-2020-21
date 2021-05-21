#pragma once

#include "Ability.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "GameMap.h"
#include "Health.h"

#include <vector>

class Ability_Priest : public AbilityStruct {
public:
	Ability_Priest(): AbilityStruct(selectorH, ShaderForm::TxT, ShaderType::nullSh) {}
	virtual ~Ability_Priest() {}
	void AbilityExecute(int x, int y);
	void finTurno() override { self->ability_usable = true; self->freeAbilityShader(); }
};