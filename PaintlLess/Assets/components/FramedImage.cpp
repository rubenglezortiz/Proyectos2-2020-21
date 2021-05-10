#include "FramedImage.h"


FramedImage::FramedImage(Texture* tex, int d, Unit p) 
{
	personaje = p;
	tr_ = nullptr;
	tex_ = tex;
	delay = d;
	time = 0;
	iniFrame = Vector2D(currentAnim, 0);

	endFrame = Vector2D(currentAnim, UnitInfo::spriteSheetInfo[personaje].animInfo[currentAnim]);
	r_ = iniFrame.getX();
	c_ = iniFrame.getY();

	auto w = tex_->width() / UnitInfo::spriteSheetInfo[personaje].cols;
	auto h = tex_->height() / UnitInfo::spriteSheetInfo[personaje].rows;
	src_ = { w * c_, h * r_, w, h };

	rows_ = UnitInfo::spriteSheetInfo[personaje].rows;
	cols_ = UnitInfo::spriteSheetInfo[personaje].cols;
	w_ = w;
	h_ = h;
}

void FramedImage::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void FramedImage::render() {
	auto& pos = tr_->getPos();
	auto h = tr_->getH();
	auto w = tr_->getW();
	auto rot = tr_->getRot();

	if (sdlutils().currRealTime() - time >= delay) { // Si se tiene que actualizar la imagen
		time = sdlutils().currRealTime();
		SDL_Rect dest = build_sdlrect(pos, w, h);
		dest.y -= 40;
		dest.x += 30;
		dest.w -= 60;
		if (c_ + 1 > endFrame.getY() - 1) {	// Si se ha llegado a la ult col
			c_ = 0;
		}
		else c_++;

		src_ = { w_ * c_, h_ * r_, w_, h_ };
		if (entity_->hasGroup<Equipo_Azul>())
			tex_->render(src_, dest, rot,nullptr,SDL_FLIP_HORIZONTAL);
		else
			tex_->render(src_, dest, rot);
	}
	else {
		SDL_Rect dest = build_sdlrect(pos, w, h);
		dest.y -= 40;
		dest.x += 30;
		dest.w -= 60;
		src_ = { w_ * c_, h_ * r_, w_, h_ };
		if (entity_->hasGroup<Equipo_Azul>())
			tex_->render(src_, dest, rot, nullptr, SDL_FLIP_HORIZONTAL);
		else
			tex_->render(src_, dest, rot);
	}
}