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
		mapa(mapa), casillasRendered(0) {};

	virtual void update() override;
	virtual void render() override;
	void setCells(std::vector<Vector2D>* arrayPointer);
	void setTexture(Texture* tex);
	void resetLerp();
	void resetCasillasRendered();
	void resetAnim();

	//Para movimiento
	static void casillasPosiblesRecu(const Vector2D& cSelected, uint casillasAMover, GameMap* mapa, std::vector<Vector2D>* casillasAPintar);
	static void casillasPosiblesRecuAux(int casillasAMover, const Vector2D& cSelected, const Vector2D& cActual, vector<vector<CasillaMov>>& casillasChecked, bool base);

private:
	std::vector<Vector2D>* arrayPointer;
	Texture* tex;
	float lerpTime;
	int casillasRendered;
	GameMap* mapa;
};

