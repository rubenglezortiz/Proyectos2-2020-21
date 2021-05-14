// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <memory>
#include "..\PaintlLess\Assets\game\Game.h"
#include <SDL_stdinc.h>

void start() {
	Game g;

	g.init();
	g.start();
}

int main(int argc, char** argv) {
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
