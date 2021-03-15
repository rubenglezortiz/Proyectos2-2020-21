// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "./Transform.h"

class Image : public Component {
public:
	Image(Texture* tex) :
		tr_(nullptr), //
		tex_(tex) //
		
	{
		src_ = { 0, 0, tex->width(), tex->height() };
	}

	Image(Texture* tex, SDL_Rect src) :
		tr_(nullptr), //
		tex_(tex), //
		src_(src)
	{
	}

	Image(Texture* tex, int rows, int cols, int r, int c) :
		tr_(nullptr), //
		tex_(tex) //
	{
		auto w = tex->width() / cols;
		auto h = tex->height() / rows;
		src_ = { w * c, h * r, w, h };
	}


	virtual ~Image() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void render() override;

private:
	Transform* tr_;
	Texture* tex_;
	SDL_Rect src_;
};
