// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <memory>
#include "..\PaintlLess\Assets\game\Game.h"
#include <SDL_stdinc.h>
#include <iomanip>
#include <Windows.h>
void start() {
	
	Game g;
	srand(time(NULL));
	g.init();
	g.start();


}

int main(int argc, char** argv) {


	FreeConsole();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try {
		start();
	}
	catch (const std::string& e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	}
	catch (const char* e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	}
	catch (const std::exception& e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	}
	catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	return 0;
}
