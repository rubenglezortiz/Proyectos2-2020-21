#pragma once
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows-
#include "..\Assets\sdlutils\SDLUtils.h"
#include "..\Assets\ecs\Manager.h"
#include "..\Assets\ecs\Entity.h"
#include "..\Assets\Transform.h"
#include "..\Assets\Image.h"
#include "..\Assets\Rectangle.h"
#include "..\Assets\ecs\Component.h"	
#include <string>
#include <fstream>
#include <array>

//#include "Game.h"
using namespace std;

typedef unsigned int uint;

class GameMap : public Component {
private:		// 0      1      2      3
	enum MapCell { Grass, Dirt, Tree, Rock };
	MapCell** cells;
	int rows, cols;
	int cellWidth, cellHeight; 
	std::string level;
public:
	GameMap(const string levelN);
	virtual ~GameMap();
	virtual void init();
	void loadMap(const string levelName);
	void render();
};