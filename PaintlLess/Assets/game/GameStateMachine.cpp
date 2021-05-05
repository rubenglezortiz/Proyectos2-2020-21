#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine() {
    while (!states.empty())
        popState();
}

void GameStateMachine::initState() {
    initChangedState = false;
    states.top()->init();
}

void GameStateMachine::popState() {
    if (!states.empty()) {
        delete states.top();
        states.pop();
    }
}

void GameStateMachine::pushState(GameState* state) {
    states.push(state);
    initChangedState = true;
}

void GameStateMachine::changeState(GameState* state) {
    popState();
    pushState(state);
}