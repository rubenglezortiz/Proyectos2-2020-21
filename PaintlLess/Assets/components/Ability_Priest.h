#pragma once

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "GameMap.h"
#include "Health.h"

#include <vector>

class Ability_Priest : public Component {
private:
	int cellWidth, cellHeight;
	bool selected = false;
	Texture* tex_;
	Transform* tr_;
	GameMap* mapa_;
	Vector2D posPriest;
	vector<Vector2D> casillasHeal;
public:
	Ability_Priest() {}
	virtual ~Ability_Priest() {}
	void init() override;
	void render() override;
	void update() override;
	void heal();
	void healingShader();
	void freeAbilityShader();

};