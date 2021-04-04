#include "./PointOnImage.h"

void PointOnImage::init() {
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	dest.h = mapa->getCellHeight();
	dest.w = mapa->getCellWidth();
}

void PointOnImage::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (sdlutils().currRealTime() > cont + 10) {

		resultado = mX / mapa->getCellWidth();
		dest.x = resultado * mapa->getCellWidth();
		resultado = mY / mapa->getCellHeight();
		dest.y = resultado * mapa->getCellHeight();
		cont = sdlutils().currRealTime();
	}
}

void PointOnImage::render() {
	tex_->render(dest);
}