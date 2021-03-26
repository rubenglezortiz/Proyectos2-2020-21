#pragma once
#include "GameState.h"

//#include "MenuButton.h"
//#include "checkML.h"
class Manager;
using namespace std;

class MainMenuState : public GameState {
private:
	const int w = 200;
	const int h = 120;
public:	
	MainMenuState(GameStateMachine* gsm);
	virtual ~MainMenuState() {};

	//Callbacks
	static void newGame(GameStateMachine* gsm);
	static void loadGame(GameStateMachine* gsm);
	static void exitApp(GameStateMachine* gsm);
};