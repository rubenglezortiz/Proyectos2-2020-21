#pragma once// This file is part of the course TPV2@UCM - Samir Genaim


#include "../ecs/Component.h"
#include "../../Assets/utils/Vector2D.h"
#include "../../Assets/sdlutils/InputHandler.h"

#include "Transform.h"

class Rotate : public Component {
public:
	Rotate() :
		tr(nullptr), rotation(10.0) {
	}

	Rotate(Transform* transform, float rot) :
		tr(transform),
		rotation(rot)
	{
	}

	virtual ~Rotate() {
	}

	void update() override {
		if (ih().keyDownEvent()) {
			auto& vel = tr->getVel();
			if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				tr->setRot(tr->getRot() - rotation);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				tr->setRot(tr->getRot() + rotation);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
				vel.setY(0.0f);
				vel.setX(0.0f);
			}
		}
	}


private:
	Transform* tr;
	float rotation;
};


