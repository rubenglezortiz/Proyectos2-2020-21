#include "ButtonDescription.h"
#include "../game/DescriptionState.h"
#include "../game/GameStateMachine.h"
#include "../sdlutils/InputHandler.h"

ButtonDescription::ButtonDescription(GameStateMachine* gsm, Texture* desc) : gsm_(gsm), desc_(desc) { }

void ButtonDescription::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void ButtonDescription::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && mY >= tr_->getPos().getY() && mY <= tr_->getH() + tr_->getPos().getY() &&
		ih().getMouseButtonState(ih().RIGHT)) {
		select_ = true;
	}
}

void ButtonDescription::render() {
	if (select_) {
		SDL_Rect dest;
		dest.x = 50; dest.y = 50; dest.w = 500; dest.h = 500;
		desc_->render(dest);
	}
}