#pragma once
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows-

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Image.h"
#include "../ecs/Component.h"

#include <string>
#include <fstream>
#include <array>

//#include "Game.h"
class Game;
using namespace std;

typedef unsigned int uint;

enum Color { Azul, Verde, Rojo, Amarillo, Ninguno};
enum TipoCasilla { Pintable, NoPintable, Base};

class PlayState;

struct Casilla
{
	Color color;
	TipoCasilla tipoCasilla;
	Entity* character;
	Entity* obstaculo;
};

class GameMap : public Component {
private:		
	Casilla** cells;
	int rows, cols;
	int cellWidth, cellHeight; 
	std::string level;
	PlayState* playState;

public:
	GameMap(const string levelN, PlayState* playState);
	virtual ~GameMap();
	virtual void init();
	void loadMap(const string levelName);
	void setColor(const Vector2D& cas, Color color);
	void setEstado(const Vector2D& cas, TipoCasilla tipo);
	void setCharacter(const Vector2D& cas, Entity* e);
	void setObstaculo(const Vector2D& cas, Entity* e);
	void removeCharacter(const Vector2D& cas);
	void removeObstaculo(const Vector2D& cas);
	bool casillaValida(const Vector2D& cas);
	bool movimientoPosible(Vector2D cas);
	bool movimientoPosibleEnredadera(Vector2D cas);
	bool ataquePosible(Vector2D cas);
	Color getColor(Vector2D cas);
	void render();
	int getRows() const { return rows; };
	int getColumns() const { return cols; }
	int getCellWidth() const { return cellWidth; };
	int getCellHeight() const { return cellHeight; };
	Entity* getCharacter(Vector2D pos) { return cells[(int)pos.getY()][(int)pos.getX()].character; }
	Entity* getObstaculo(Vector2D pos) { return cells[(int)pos.getY()][(int)pos.getX()].obstaculo; }
	TipoCasilla getTipoCasilla(Vector2D pos) { return cells[(int)pos.getY()][(int)pos.getX()].tipoCasilla; }
	PlayState* getPlayState() { return playState; }

	Vector2D MapCoordsToSDLPoint(Vector2D coords) const { //Pasar de coordenadas del mapa a pixeles
		Vector2D p{ (coords.getX() * cellWidth) , (coords.getY() * cellHeight)/* + DESPL*/ };
		//cout << p.getX() << " " << p.getY() << endl;
		return p;
	}

	Vector2D SDLPointToMapCoords(Vector2D p) { //Pasar de pixeles a coordenadas del mapa
		//como las casillas neceitan int se hace aqui el casteo
		int X = p.getX() / cellWidth;
		int Y = p.getY()/*-DESPL*/ / cellHeight;
		//como vector2D es float se hace el casteo pero el valor va a ser .0000
		Vector2D coords{ (float)X,(float)Y };
		//cout << coords.getX() << " " << coords.getY() << endl;
		return coords;
	}		
};