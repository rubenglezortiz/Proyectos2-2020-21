#include "DescriptionState.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../game/GameStateMachine.h"

DescriptionState::DescriptionState(GameStateMachine* gsm, Texture* desc) : GameState(gsm) {
	desc_ = desc;
}

void DescriptionState::update() {
	sdlutils().presentRenderer();
}