#pragma once
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows-
#include "..\Assets\sdlutils\SDLUtils.h"
#include "..\Assets\ecs\Manager.h"
#include "..\Assets\ecs\Entity.h"
#include "..\Assets\Transform.h"
#include "..\Assets\Image.h"
#include "..\Assets\Rectangle.h"
#include <string>
#include <fstream>
#include <array>

//#include "Game.h"
using namespace std;

typedef unsigned int uint;

class Game;

class GameMap {
private:		// 0      1      2      3
	enum MapCell { Grass, Dirt, Tree, Rock };
	MapCell** cells;
	Game* game;
	Manager* _mng;
	int rows, cols;
	int cellWidth, cellHeight;
public:
	GameMap(int rows, int cols, Game* g);
	~GameMap();
	void loadMap(const string levelName);
	void render();
};