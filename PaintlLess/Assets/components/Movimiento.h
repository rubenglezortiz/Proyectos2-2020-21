#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "./MovementShader.h"

class Movimiento : public Component {
public:
	Movimiento() : tr_(nullptr), mapa(nullptr), selected(false), movShader(nullptr), cellWidth(0),cellHeight(0) {}
	virtual ~Movimiento() {};

	void init() override;
	void update() override;

private:
	vector<vector<MovementShader::CasillaMov>> casillasChecked;
	MovementShader* movShader;
	Transform* tr_;
	GameMap* mapa;
	bool selected;
	int cellWidth, cellHeight;

	void initializeCasillasChecked();
	void resetCasillasChecked();
};

