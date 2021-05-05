#pragma once

#include "GameState.h"

class GameStateMachine; 
class Texture;

class DescriptionState : public GameState {
private:
	Texture* desc_;
public:
	DescriptionState(GameStateMachine* gsm, Texture* desc);
	~DescriptionState() {}
	void update() override;
};