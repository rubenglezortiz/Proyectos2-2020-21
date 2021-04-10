#include "Rectangle.h"

void Rectangle::render() {

	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color_));

	SDL_Rect rect = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());

	SDL_RenderFillRect(sdlutils().renderer(), &rect);
}