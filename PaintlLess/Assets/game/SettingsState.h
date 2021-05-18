#pragma once
#include "GameState.h"
#include "PlayState.h"

class SettingsState : public GameState {

private:
	PlayState* playState_;
public:
	SettingsState(GameStateMachine* gsm, PlayState* pS = nullptr);
	~SettingsState() {}
	void update() override;
	static void goBack(GameStateMachine* gsm);
	static void tickVolume(bool state);
	static void surrender(GameStateMachine* gsm);
};