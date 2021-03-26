#pragma once
#include "GameState.h"

class PlayState : public GameState
{
public:
	PlayState(GameStateMachine* gsm);
	virtual ~PlayState();
};