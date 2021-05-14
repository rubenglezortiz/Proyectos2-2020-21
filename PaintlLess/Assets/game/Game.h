// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <memory>
#include "GameStateMachine.h"
#include "Network.h"


// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
//class Manager;

class Game {
public:
	Game();
	virtual ~Game();
	void init(const char* host, Uint16 port);
	void start();
private:
	Network* net;
	//std::unique_ptr<Manager> mngr_;
	GameStateMachine* stateMachine;
};
