#include "../ecs/Manager.h"
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"

GameState::GameState() {
	mngr_.reset(new Manager());
}

GameState::~GameState() {

}

void GameState::update() { //run
	mngr_->update();
	mngr_->refresh();

	sdlutils().clearRenderer();
	mngr_->render();
	sdlutils().presentRenderer();
}

void GameState::init() {

}