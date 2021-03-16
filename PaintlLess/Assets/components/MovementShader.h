// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "GameMap.h"

class MovementShader : public Component {
public:
	MovementShader(Texture* tex) :
		tex_(tex) //
	{
		cont = 0;







		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;

		dest.x = mX;
		dest.y = mY;
		dest.h = tex_->height();
		dest.w = tex_->width();
	}

	virtual ~MovementShader() {
	}

	void init() override {
		mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
		
		dest.h = mapa->getCellHeight();
		dest.w = mapa->getCellWidth();
	}

	void update() override {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;

		if (sdlutils().currRealTime() > cont + 100) {


			resultado = mX / mapa->getCellHeight();
			dest.x = resultado *  mapa->getCellHeight();
			resultado = mY / mapa->getCellWidth();
			dest.y = resultado *  mapa->getCellWidth();
			

			
			cont = sdlutils().currRealTime();
		}

	}

	void render() override
	{
		tex_->render(dest);
	}


private:
	int cont;
	SDL_Rect dest;
	GameMap* mapa;
	int resultado;

	Vector2D position;
	Texture* tex_;
	SDL_Rect src_;
};

