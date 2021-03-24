#pragma once

#include <stack>
#include "GameState.h"
//#include "checkML.h"

using namespace std;

class GameStateMachine {
private:
    stack<GameState*> states; //Pila de estados
public:
    GameStateMachine() {}; //Constructora
    ~GameStateMachine();  //Destructora

    GameState* currentState() { return states.top(); }; //Devuelve el estado actual
    void popState();                                    //Saca estado de la pila
    void pushState(GameState* state);                    //Introduce estado en la pila
    void changeState(GameState* state);                    //Cambio de estado
};