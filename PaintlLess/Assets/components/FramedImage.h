#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

class FramedImage : public Component {
public:
	
	FramedImage(Texture* tex, int rows, int cols, int d, Vector2D initFrame, Vector2D endFrame);
	virtual ~FramedImage() {}
	void init() override;
	void render() override;

private:
	Transform* tr_;
	Texture* tex_;
	SDL_Rect src_;
	Vector2D iniFrame, endFrame;
	Uint32 time;
	int delay;
	int rows_, cols_;	 // number of rows & cols in the texture
	int w_, h_;			 // width & height of the texture
	int r_, c_;			 // row & col to render
};