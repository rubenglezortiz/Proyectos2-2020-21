#include "Image.h"

void Image::render()  {
	SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
	tex_->render(src_, dest, tr_->getRot());
}