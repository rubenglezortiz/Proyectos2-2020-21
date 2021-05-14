#pragma once

#include <stack>
#include "GameState.h"
#include "../../CharactersSelected.h"
#include "Network.h"

//#include "checkML.h"

using namespace std;

class GameStateMachine {
private:
	stack<GameState*> states;    // Pila de estados.
	CharactersSelected* charSel; // Vector de personajes.
	Network* net;

	bool initChangedState;
	GameState* lastChanged;
	uint popState_ = 0;
	bool online = false;
public:
	// Constructora.
	GameStateMachine() : lastChanged(nullptr), initChangedState(false) { charSel = new CharactersSelected();  net = new Network(); };
	// Destructora.
	~GameStateMachine();

	bool initChanged() { return initChangedState; };
	void initOnline();

	void initState();
	void update();
	void setOnline(bool a) { online = a; };

	void refresh();

	// Devuelve el estado actual.
	GameState* currentState() { return states.top(); };
	// Saca estado de la pila.
	void popState();
	// Introduce estado en la pila.
	void pushState(GameState* state);
	// Cambio de estado.
	void changeState(GameState* state);
	// Devuelve el puntero a CharactersSelected.
	CharactersSelected* &getCharSel() { return charSel; };
};