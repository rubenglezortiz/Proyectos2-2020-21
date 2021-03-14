#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "./Transform.h"
#include "./Image.h"
#include "../ecs/Entity.h"


class PointOnImage : public Component {
public:
	PointOnImage() :
		im(nullptr)
	{
	}

	PointOnImage(Image* image) :
		im(image)
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

		if (mX > pos.getX() && mX < pos.getX() + rect.getX() && mY > pos.getY() && mY < pos.getY() + rect.getY())
			std::cout << "collision";
	}


private:
	Vector2D pos;
	Vector2D rect;
	Image* im;
};

