// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <cassert>

#include "../PaintlLess/Assets/ecs/Component.h"
#include "../PaintlLess/Assets/sdlutils/InputHandler.h"
#include "../PaintlLess/Assets/ecs/Entity.h"
#include "Transform.h"

class KeyBoardCtrl : public Component {
public:
	KeyBoardCtrl() :
		tr_(nullptr), speed_(10.0) {
	}
	virtual ~KeyBoardCtrl() {
	}


	inline void setSpeed(float speed) {
		speed_ = speed;
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			auto& vel = tr_->getVel();
			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				vel.setY(-speed_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_DOWN)) {
				vel.setY(speed_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				vel.setX(-speed_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				vel.setX(speed_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
				vel.setY(0.0f);
				vel.setX(0.0f);
			}
		}
	}

private:
	Transform* tr_;
	float speed_;
}
;

