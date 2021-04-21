#pragma once

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "GameMap.h"
#include "Health.h"

#include <vector>

class Ability_Priest : public Ability {
public:
	Ability_Priest():Ability(selectorH) {}
	virtual ~Ability_Priest() {}
	void update() override;
	void heal();

private:
	Vector2D posPriest;
};