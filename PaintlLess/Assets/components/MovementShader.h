// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

class MovementShader : public Component {
public:
	MovementShader(Texture* tex) :
		tex_(tex) //
	{
		src_ = { 0, 0, tex->width(), tex->height() };
	}

	virtual ~MovementShader() {
	}

	void render() override
	{

	}


private:
	Vector2D position;
	Texture* tex_;
	SDL_Rect src_;
};

