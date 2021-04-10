#pragma once
#include "GameState.h"
#include "CharacterSelectionState.h"

//#include "MenuButton.h"
//#include "checkML.h"
class Manager;
using namespace std;

class MainMenuState : public GameState {
private:
	const int w = 150;
	const int h = 70;
public:	
	MainMenuState(GameStateMachine* gsm);
	virtual ~MainMenuState() {};

	//Callbacks
	static void newGame(GameStateMachine* gsm);
	static void loadGame(GameStateMachine* gsm);
	static void exitApp(GameStateMachine* gsm);
};