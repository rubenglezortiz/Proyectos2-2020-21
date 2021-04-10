#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "GameMap.h"
#include "../sdlutils/InputHandler.h"

class PointOnImage : public Component {
public:
	PointOnImage(Texture* tex) :
		tex_(tex), mapa(nullptr), resultado(0), src_(SDL_Rect()) //
	{
		cont = 0;
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		dest.x = mX;
		dest.y = mY;
		dest.h = tex_->height();
		dest.w = tex_->width();
	}

	virtual ~PointOnImage() {
	}

	void init() override;
	void update() override;
	void render() override;

private:
	int cont;
	SDL_Rect dest;
	GameMap* mapa;
	int resultado;

	Vector2D position;
	Texture* tex_;
	SDL_Rect src_;
};