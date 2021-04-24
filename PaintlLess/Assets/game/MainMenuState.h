#pragma once
#include "GameState.h"
#include "CharacterSelectionState.h"

//#include "MenuButton.h"
//#include "checkML.h"
class Manager;
using namespace std;

class MainMenuState : public GameState {
private:
	const int w = 155;
	const int h = 75;
public:	
	MainMenuState(GameStateMachine* gsm);
	virtual ~MainMenuState() {};

	//Callbacks
	static void newGame(GameStateMachine* gsm);
	static void loadGame(GameStateMachine* gsm);
	static void exitApp(GameStateMachine* gsm);
};