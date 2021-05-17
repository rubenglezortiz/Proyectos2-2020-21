#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine() {
	popState_ = states.size();
	refresh();
}

void GameStateMachine::initOnline()
{
	net->init(this);
	setOnline(true);
	charSel->setEquipo(net->isMaster() ? 0 : 1); //Master: Equipo 0
}

void GameStateMachine::initState() {
	initChangedState = false;
	states.top()->init();
}

void GameStateMachine::update()
{
	currentState()->update(); //update del GameState
	if (online) net->update();
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
	if (lastChanged == nullptr)
		popState();
	else
		delete lastChanged;
	lastChanged = state;
}