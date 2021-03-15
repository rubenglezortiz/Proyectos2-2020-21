#include "Image.h"

void Image::render()  {
	SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
	tex_->render(src_, dest, tr_->getRot());
}

void Image::shiny() {
	if (src_.x < 3 * src_.w) //el 3 est� cableado por c�digo
		src_.x += src_.w;
}

void Image::dark() {
	src_.x = currFrame;
}