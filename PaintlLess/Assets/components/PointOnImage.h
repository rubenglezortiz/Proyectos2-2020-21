//#pragma once
//
//#include "../ecs/Component.h"
//#include "../sdlutils/InputHandler.h"
//#include "./Transform.h"
//#include "./Image.h"
//#include "../ecs/Entity.h"
//
//
//class PointOnImage : public Component {
//public:
//	PointOnImage() :
//		im(nullptr), pos(Vector2D()), rect(Vector2D()), cont(0)
//	{
//	}
//
//	PointOnImage(Image* image) :
//		im(image), pos(Vector2D()), rect(Vector2D()), cont(0)
//	{
//	}
//
//
//	virtual ~PointOnImage() {
//	}
//
//	void init()override {
//		pos = entity_->getComponent<Transform>()->getPos();
//		rect.setX(entity_->getComponent<Transform>()->getW());
//		rect.setY(entity_->getComponent<Transform>()->getH());
//
//		//imagen...
//	}
//
//	void update() override {
//		int mX = ih().getMousePos().first;
//		int mY = ih().getMousePos().second;
//
//		/*if (sdlutils().currRealTime() > cont + 150) {
//
//			if (mX > pos.getX() && mX < pos.getX() + rect.getX() && mY > pos.getY() && mY < pos.getY() + rect.getY())		im->shiny();
//
//			else im->dark();
//			cont = sdlutils().currRealTime();
//		}*/
//	}
//
//
//private:
//	Vector2D pos;
//	Vector2D rect;
//	Image* im;
//	int cont;
//};
//
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "GameMap.h"
#include "../sdlutils/InputHandler.h"
#include "../game/LerpingFunctions.h"
#include "../game/OffsetInfo.h"

class PointOnImage : public Component {
public:
	PointOnImage(Texture* tex) : tex_(tex), mapa(nullptr), resultado(0), src_(SDL_Rect())  {
		cont = 0;
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		dest.x = mX;
		dest.y = mY+ OFFSET_Y;
		dest.h = tex_->height();
		dest.w = tex_->width();
	}

	virtual ~PointOnImage() {
	}

	void init() override;
	void update() override;
	void render() override { tex_->render(dest); }


private:
	int cont;
	SDL_Rect dest;
	GameMap* mapa;
	int resultado;

	Vector2D position;
	Texture* tex_;
	SDL_Rect src_;

	//Animation
	Vector2D currentPosition;
	Vector2D lastPosition;
	float lerpTime = 0;
};