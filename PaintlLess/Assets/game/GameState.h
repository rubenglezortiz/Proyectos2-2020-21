#pragma once

#include <memory>

// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager; //#include "../ecs/Manager.h"-------------------------------------------

class GameState { //hereda de GameState
public:
	GameState();
	virtual ~GameState();
	virtual void init();
	virtual void update();
	
protected:
	std::unique_ptr<Manager> mngr_; 
	//unique pointer se hace delete a si mismo al terminar la ejecucion
};
