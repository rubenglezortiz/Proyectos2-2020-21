#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <vector>
#include "../sdlutils/Texture.h"
#include "GameMap.h"
#include "../game/OffsetInfo.h"

struct CasillaMov {
	bool checked;
	bool movPosible;
};

class UniversalShader : public Component
{
public:
	UniversalShader(GameMap* mapa) : 
		arrayPointer(nullptr), tex(nullptr), lerpTime(0),
		mapa(mapa), casillasRendered(0), delayedCellsRender(true) {};

	virtual void update() override;
	virtual void render() override;
	void setCells(std::vector<Vector2D>* arrayPointer);
	void setTexture(Texture* tex);
	void resetLerp();
	void resetCasillasRendered();
	void resetAnim();
	void setDelayCellsRender(bool&& delay) { delayedCellsRender = delay; }

	//Para movimiento, ataque y habilidad respectivamente
	static void checkCasillasPosiblesMov(const Vector2D& cSelected, uint casillasAMover, GameMap* mapa, std::vector<Vector2D>* casillasAPintar);
	static void attackShader(const Vector2D& pos, GameMap* mapa, std::vector<Vector2D>* casillasAtaque, int range);
private:
	std::vector<Vector2D>* arrayPointer;
	Texture* tex;
	float lerpTime;
	int casillasRendered;
	GameMap* mapa;

	bool delayedCellsRender;
};

