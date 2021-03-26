#include "MenuButton.h"

MenuButton::MenuButton(GameStateMachine* gsm, CallBackOnClick* cb) {
	gsm_ = gsm;
	cbOnClick = cb;
}

void MenuButton::init()  {
	tr_ = entity_->getComponent<Transform>();	
	assert(tr_ != nullptr);
}

void  MenuButton::update() {	//Falta sombreado hover
	if (ih().mouseButtonEvent()) {
		auto& pos = tr_->getPos();
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (ih().getMouseButtonState(ih().LEFT) && mX > pos.getX() && mX < pos.getX() + tr_->getW() && mY > pos.getY() && mY < pos.getY() + tr_->getH()) {
			cbOnClick(gsm_);
		}
	}
}