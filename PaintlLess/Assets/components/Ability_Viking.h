#pragma once

#include "./Ability.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "./Health.h"
#include "./Movimiento.h"
#include "./FramedImage.h"

class Ability_Viking : public Ability {
public:
	Ability_Viking() : Ability(selectorA, ShaderForm::VikingForm, ShaderType::nullSh) {}
	virtual ~Ability_Viking() {}
	void AbilityExecute(int x, int y);
	virtual bool abilityCheck(const Vector2D& pos);
	void finTurno() override { ability_usable = true; freeAbilityShader(); }
};
