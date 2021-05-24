#include "ButtonSurrender.h"
#include "Transform2.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../game/PlayState.h"
#include "../game/FinState.h"
#include "../game/GameStateMachine.h"

ButtonSurrender::ButtonSurrender(PlayState* pst) : pst_(pst){}

void ButtonSurrender::init(){
	tr_ = entity_->getComponent<Transform2>();
	assert(tr_ != nullptr);
}

void ButtonSurrender::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && mY >= tr_->getPos().getY() && mY <= tr_->getH() + tr_->getPos().getY() &&
		ih().getMouseButtonState(ih().LEFT)) {
		pst_->getGSM()->getNetworkManager()->sendEndGame();
		//pst_->getGSM()->getNetworkManager()->restartConnection();
		pst_->getGSM()->changeState(new FinState(pst_->getGSM(), (pst_->getCurrentPlayer() + 1)%2, pst_->getPorcentaje()));
	}
}