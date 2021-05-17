#pragma once
#include "GameState.h"
class WaitForCharacterSelectionState : public GameState
{
public:
	WaitForCharacterSelectionState(GameStateMachine* gsm) : GameState(gsm) {};
};

