#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine() {
    while (!states.empty())
        popState();
}

void GameStateMachine::popState() {
    if (!states.empty()) {
        delete states.top();
        states.pop();
    }
}

void GameStateMachine::pushState(GameState* state) {
    states.push(state);
}

void GameStateMachine::changeState(GameState* state) {
    popState();
    pushState(state);
}