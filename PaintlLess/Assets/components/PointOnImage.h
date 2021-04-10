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

	void init() override {
		mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();

		dest.h = mapa->getCellHeight();
		dest.w = mapa->getCellWidth();
	}

	void update() override {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;

		//Ver si la posición actual del cursor es igual a la anterior
		//La posicion se guarda en coordenadas de mapa porque que coordenadas SDL no podemos
		//ver cuando cambia de casilla
		if (!(mapa->SDLPointToMapCoords({ (float)mX, (float)mY }) == currentPosition))
		{
			lastPosition = currentPosition; //Si no lo es, la ultima posicion es la actual anterior
			currentPosition = mapa->SDLPointToMapCoords({ (float)mX, (float)mY }); //Actualizamos la actual
			lerpTime = 0; //Activamos el lerp
		}

		if (lerpTime < 1) lerpTime += 0.1; //Aumentar el lerp

		if (sdlutils().currRealTime() > cont + 10) {

			//Convertir posiciones de mapa a SDL
			Vector2D lastPosSDL = mapa->MapCoordsToSDLPoint(lastPosition);
			Vector2D currentPosSDL = mapa->MapCoordsToSDLPoint(currentPosition);

			dest.x = LerpFuncts::Lerp(lastPosSDL.getX(), currentPosSDL.getX(), lerpTime);
			dest.y = LerpFuncts::Lerp(lastPosSDL.getY(), currentPosSDL.getY(), lerpTime);
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

	//Animation
	Vector2D currentPosition;
	Vector2D lastPosition;
	float lerpTime = 0;
};