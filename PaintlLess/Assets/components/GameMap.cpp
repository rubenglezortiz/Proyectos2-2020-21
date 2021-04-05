#include "GameMap.h"
#include <iostream>
#include <fstream>

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "../game/Game.h"
#include "./PointOnImage.h"

using namespace std;

GameMap::GameMap(const string levelN) {
	level = levelN;
}

GameMap::~GameMap() {
	for (int r = 0; r < rows; ++r)
		delete[] cells[r];
	delete[] cells;
}

void GameMap::init() {
	loadMap(level);
}
void GameMap::loadMap(const string levelName) {

	tmx::Map map;
	if (map.load(sdlutils().tiled()))
	{
		const auto& layers = map.getLayers();
		for (const auto& layer : layers)
		{
			if (layer->getType() == tmx::Layer::Type::Tile)
			{
				const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
				//read out tile layer properties etc...

				cols = tileLayer.getSize().x; rows = tileLayer.getSize().y;
				cells = new Casilla * [rows];
				for (int r = 0; r < rows; ++r) {
					for (int c = 0; c < cols; ++c) {
						cells[r] = new Casilla[cols];
					}
				}

				cellWidth = sdlutils().width() / cols;
				cellHeight = sdlutils().height() / rows;

				auto tiles = tileLayer.getTiles();
				for (int i = 0; i < rows; ++i) {
					for (int j = 0; j < cols; ++j) {
						auto* casilla = entity_->getMngr()->addEntity();

						casilla->addComponent<Transform>(Vector2D(j * cellWidth, i * cellHeight), cellWidth, cellHeight);

						casilla->addComponent<Image>(&sdlutils().images().at("tileset0"), 1, 4, 0, tiles[i * cols + j].ID - 1);

						switch (tiles[i * cols + j].ID) {
						case 1: // Base
							cells[i][j].color = Color::Ninguno;
							cells[i][j].tipoCasilla = TipoCasilla::Base;
							break;
						case 2: // Roca
							cells[i][j].color = Color::Ninguno;
							cells[i][j].tipoCasilla = TipoCasilla::NoPintable;
							break;
						case 3: // Agua
							cells[i][j].color = Color::Ninguno;
							cells[i][j].tipoCasilla = TipoCasilla::Pintable;
							break;
						case 4: // Cesped
							cells[i][j].color = Color::Ninguno;
							cells[i][j].tipoCasilla = TipoCasilla::Pintable;
							break;
						}
						cells[i][j].character = nullptr;
					}
				}
			}
		}

	}

	//ifstream file;
	//file.open(levelName);
	//if (!file.is_open())  throw string("No se encuentra el fichero");
	//else {
	//	int type;
	//	file >> rows >> cols;
	//	cells = new Casilla * [rows];
	//	for (int r = 0; r < rows; ++r) {
	//		for (int c = 0; c < cols; ++c) {
	//			cells[r] = new Casilla[cols];
	//		}
	//	}
	//	cellHeight = sdlutils().height() / rows;
	//	cellWidth = sdlutils().width() / cols;
	//	for (int i = 0; i < rows; ++i) {
	//		for (int j = 0; j < cols; ++j) {
	//			auto* casilla = entity_->getMngr()->addEntity();
	//			casilla->addComponent<Transform>(Vector2D(j * cellWidth, i * cellHeight), cellWidth, cellHeight);

	//			file >> type;
	//			switch (type) {
	//			case 0: // Base
	//				casilla->addComponent<Image>(&sdlutils().images().at("tileset0"), 1, 4, 0, 0);
	//				cells[i][j].color = Color::Ninguno;
	//				cells[i][j].tipoCasilla = TipoCasilla::Base;
	//				break;
	//			case 1: // Roca
	//				casilla->addComponent<Image>(&sdlutils().images().at("tileset0"), 1, 4, 0, 3);
	//				cells[i][j].color = Color::Ninguno;
	//				cells[i][j].tipoCasilla = TipoCasilla::Pintable;
	//				break;
	//			case 2: // Agua
	//				casilla->addComponent<Image>(&sdlutils().images().at("tileset0"), 1, 4, 0, 1);
	//				cells[i][j].color = Color::Ninguno;
	//				cells[i][j].tipoCasilla = TipoCasilla::NoPintable;
	//				break;
	//			case 3: // Cesped
	//				casilla->addComponent<Image>(&sdlutils().images().at("tileset0"), 1, 4, 0, 2);
	//				cells[i][j].color = Color::Ninguno;
	//				cells[i][j].tipoCasilla = TipoCasilla::Pintable;
	//				break;
	//			}

	//			cells[i][j].character = nullptr;
	//		}
	//	}
	//}
	//file.close();

}

void GameMap::render() {
	/*SDL_Rect desRect;

	desRect.h = sdlutils().height();
	desRect.w = sdlutils().width();
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			desRect.x = c * desRect.w;
			desRect.y = r * desRect.h;
		}
	}*/
}

void GameMap::setColor(const Vector2D& cas, Color color) {
	if (getColor(cas) != color && cells[(int)cas.getY()][(int)cas.getX()].tipoCasilla == Pintable) {
		auto* pintar = entity_->getMngr()->addEntity();
		cout << cas.getX() << " " << cas.getY() << endl;
		pintar->addComponent<Transform>(Vector2D(cas.getX(), cas.getY()), cellWidth, cellHeight);
		pintar->addComponent<Image>(&sdlutils().images().at("star"));

		cells[(int)cas.getY()][(int)cas.getX()].color = color;
		cout << "Color: " << getColor(cas) << endl;
	}
}

void GameMap::setEstado(const Vector2D& cas, TipoCasilla tipo) {
	assert(casillaValida(cas)); //si a este método se le pasa una casilla de fuera del mapa, error de ejecución
	cells[(int)cas.getY()][(int)cas.getX()].tipoCasilla = tipo;
}

void GameMap::setCharacter(const Vector2D& cas, Entity* e) {
	cells[(int)cas.getY()][(int)cas.getX()].character = e;
}

void GameMap::removeCharacter(const Vector2D& cas) {
	cells[(int)cas.getY()][(int)cas.getX()].character = nullptr;
}


// Salta excepción al no encontrar 4 casillas en el borde inferior.
bool GameMap::movimientoPosible(Vector2D cas) {
	if (!casillaValida(cas))return false;
	int x = cas.getX(); int y = cas.getY();
	return (cells[y][x].tipoCasilla != NoPintable && cells[y][x].character == nullptr);
}


Color GameMap::getColor(Vector2D cas) {
	return cells[(int)cas.getY()][(int)cas.getX()].color;
}

bool GameMap::casillaValida(const Vector2D& cas) //SUPONEMOS QUE ESTÁ BIEN, ACEPTAMOS CAMBIOS XDD
{
	return cas.getX() >= 0 && cas.getX() < getColumns() && cas.getY() >= 0 && cas.getY() < getColumns() < getRows();
}

//GameMap GameMap::CreaMapa(string filename) {
//	MapCell s = MapCell.Empty;
//	ifstream in(filename);
//	int fil, col, temp;
//	in >> fil >> col;
//	GameMap m(fil,col);
//	for (int i = 0; i < fil; i++) {
//		for (int j = 0; i < col; i++) {
//			in >> temp;
//			if (temp == 0 || (temp >= 4 && temp <= 9))
//				//m[i, j] = MapCell.Empty;
//			else if(temp == 1)
//				//m[i, j] = MapCell.Wall;
//			else if (temp == 2)
//				//m[i, j] = MapCell.Food;
//			else if (temp == 3)
//				//m[i, j] = MapCell.Vitamins
//			else
//				//throw exception string("Tipo de casilla invalido");
//		}
//	}	
//	in.close();
//}