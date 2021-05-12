// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <memory>
#include "..\PaintlLess\Assets\game\Game.h"
#include <SDL_stdinc.h>

void start(int argc, char** argv) {
	Game g;
	Uint16 port;
	const char* host = nullptr;
	if (argc == 2) {
		atoi(argv[1]);
		port = static_cast<Uint16>(atoi(argv[1]));
	}
	else if (argc == 3) {
		host = argv[1];
		port = static_cast<Uint16>(atoi(argv[2]));
	}
	else {
		throw "Unknown mode";
	}

	g.init(host, port);
	g.start();
}

int main(int argc, char** argv) {
	try {
		start(argc, argv);
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
