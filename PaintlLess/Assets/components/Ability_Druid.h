#pragma once

#include "./Ability.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "../sdlutils/InputHandler.h"
#include "Movimiento.h"
#include "Health.h"

class PlayState;
class Ability_Druid : public Ability {
public:
	Ability_Druid(PlayState* p, int e) : Ability(selector, ShaderForm::Cross, ShaderType::DruidaSh), dest(SDL_Rect()), equip(e), pSt(p) {}
	virtual ~Ability_Druid() {}

	void finTurno() override;
	void AbilityExecute(int x, int y);

private:
	PlayState* pSt;
	SDL_Rect dest;
	Vector2D posDruid;
	bool habilidad = true;
	int equip;

	//cuando se metan margenes hay que tener cuidadd y sumarlos
};
