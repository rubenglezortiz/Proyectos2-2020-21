#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "./Transform.h"
#include "./Image.h"
#include "../ecs/Entity.h"


class PointOnImage : public Component {
public:
	PointOnImage() :
		im(nullptr), pos(Vector2D()), rect(Vector2D()), cont(0)
	{
	}

	PointOnImage(Image* image) :
		im(image), pos(Vector2D()), rect(Vector2D()), cont(0)
	{
	}


	virtual ~PointOnImage() {
	}

	void init()override {
		pos = entity_->getComponent<Transform>()->getPos();
		rect.setX(entity_->getComponent<Transform>()->getW());
		rect.setY(entity_->getComponent<Transform>()->getH());

		//imagen...
	}

	void update() override {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;

		/*if (sdlutils().currRealTime() > cont + 150) {

			if (mX > pos.getX() && mX < pos.getX() + rect.getX() && mY > pos.getY() && mY < pos.getY() + rect.getY())		im->shiny();

			else im->dark();
			cont = sdlutils().currRealTime();
		}*/
	}


private:
	Vector2D pos;
	Vector2D rect;
	Image* im;
	int cont;
};

