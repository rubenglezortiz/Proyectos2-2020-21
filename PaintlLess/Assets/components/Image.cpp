#include "Image.h"

void Image::render()  {
	if (tr_ != nullptr) {
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		if (entity_->hasGroup<Personajes>()) {
			dest.y -= 50;
			dest.w -= 20;
		}
		tex_->render(src_, dest, tr_->getRot());
	}
	else {
		SDL_Rect dest = build_sdlrect(tr2_->getPos(), tr2_->getW(), tr2_->getH());
		if (entity_->hasGroup<Personajes>()) {
			dest.y -= 50;
			dest.w = dest.w -  2 * tr2_->getW();
		}
		tex_->render(src_, dest, tr2_->getRot());
	}
}

void Image::shiny() {
	if (src_.x < 3 * src_.w) //el 3 está cableado por código
		src_.x += src_.w;
}

void Image::dark() {
	src_.x = currFrame;
}