#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../game/OffsetInfo.h"
#include "Movimiento.h"
#include "Health.h"

class Ability_Wolf : public Component {
public:
	Ability_Wolf() {}
	virtual ~Ability_Wolf() {}

	void init() override;
	void render() override;
	void update() override;
	void shaderAttack();
	void freeShader() { shader.clear(); }
	void blow();

private:
	Vector2D posWolf;
	GameMap* mapa;
	Texture* tex;
	std::vector<Vector2D> casillas;
	std::vector<Vector2D> shader;

	bool selected = false;
	int cellWidth, cellHeight;
};
