#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <vector>
#include "../sdlutils/Texture.h"
#include "GameMap.h"
#include "../game/OffsetInfo.h"

class UniversalShader : public Component
{
public:
	UniversalShader(GameMap* mapa) : 
		arrayPointer(nullptr), tex(nullptr), lerpTime(0),
		mapa(mapa), casillasRendered(0) {};

	virtual void update() override;
	virtual void render() override;
	void setCells(std::vector<Vector2D>* arrayPointer);
	void setTexture(Texture* tex);
	void resetLerp();
	void resetCasillasRendered();
private:
	std::vector<Vector2D>* arrayPointer;
	Texture* tex;
	float lerpTime;
	int casillasRendered;
	GameMap* mapa;
};

