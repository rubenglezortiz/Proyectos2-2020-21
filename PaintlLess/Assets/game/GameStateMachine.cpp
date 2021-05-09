#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine() {
    popState_ = states.size();
    refresh();
}

void GameStateMachine::initState() {
    initChangedState = false;
    states.top()->init();
}

void GameStateMachine::refresh() {
    while (!states.empty() && popState_ > 0) {
        delete states.top();
        states.pop();
        popState_--;
    }
    if (popState_ > 0) popState_ = 0;
    if (lastChanged != nullptr) {
        pushState(lastChanged);
        lastChanged = nullptr;
    }
}

void GameStateMachine::popState() {
    popState_++;
}

void GameStateMachine::pushState(GameState* state) {
    states.push(state);
    initChangedState = true;
}

void GameStateMachine::changeState(GameState* state) {
    if (lastChanged != nullptr)
        popState();
    else
        delete lastChanged;
    lastChanged = state;
}