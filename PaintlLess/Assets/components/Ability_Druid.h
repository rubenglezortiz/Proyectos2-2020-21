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
	Ability_Druid(PlayState* p, int e) : dest(SDL_Rect()), equip(e), pSt(p) {}
	virtual ~Ability_Druid() {}

	void update() override;
	void finTurno() override;	
	void generateCreeper(int x, int y);

private:	
	PlayState* pSt;
	SDL_Rect dest;
	Vector2D posDruid;
	bool habilidad = true;
	int equip;

	//cuando se metan margenes hay que tener cuidadd y sumarlos
};
