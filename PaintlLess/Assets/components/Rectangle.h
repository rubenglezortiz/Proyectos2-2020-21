// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>

#include "..\ecs\Component.h"
#include "..\ecs\Entity.h"
#include "..\sdlutils\SDLUtils.h"
#include "Transform.h"

class Rectangle : public Component {
public:
	Rectangle() :
		Rectangle(build_sdlcolor(0xffffffff)) {
	}
	Rectangle(SDL_Color color) :
		color_(color), //
		tr_(nullptr) {
	}
	virtual ~Rectangle() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);

	}
	void render() override;
private:
	SDL_Color color_;
	Transform* tr_;
};
