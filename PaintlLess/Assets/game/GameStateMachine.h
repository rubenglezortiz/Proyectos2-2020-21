#pragma once

#include <stack>
#include "GameState.h"
#include "../../CharactersSelected.h"
//#include "checkML.h"

using namespace std;

class GameStateMachine {
private:
	stack<GameState*> states;    // Pila de estados.
	CharactersSelected* charSel; // Vector de personajes.
	bool initChangedState;
	GameState* lastChanged;
	uint popState_ = 0;
public:
	// Constructora.
	GameStateMachine(): lastChanged(nullptr), initChangedState(false) { charSel = new CharactersSelected(); };
	// Destructora.
	~GameStateMachine();

	bool initChanged() { return initChangedState; };

	void initState();

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