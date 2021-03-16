#pragma once
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows-

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Image.h"
#include "Rectangle.h"
#include "../ecs/Component.h"

#include <string>
#include <fstream>
#include <array>

//#include "Game.h"
class Game;
using namespace std;

typedef unsigned int uint;

enum Color { Azul, Verde, Rojo, Amarillo, Ninguno};
enum TipoCasilla { Pintable, NoPintable};

struct Casilla
{
	Color color;
	TipoCasilla casilla;
	Entity* character;
};

class GameMap : public Component {
private:		
	Casilla** cells;
	int rows, cols;
	int cellWidth, cellHeight; 
	std::string level;
public:
	GameMap(const string levelN);
	virtual ~GameMap();
	virtual void init();
	void loadMap(const string levelName);
	void render();
	int getCellWidth() const { return cellWidth; };
	int getCellHeight() const { return cellHeight; };
};