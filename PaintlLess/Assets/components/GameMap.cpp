#include "GameMap.h"
#include <iostream>
#include <fstream>
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
	ifstream file;
	file.open(levelName);
	if (!file.is_open())  throw string("No se encuentra el fichero");
	else {
		int rows, cols, type;
		file >> rows >> cols;
		cells = new Casilla * [rows];
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				cells[r] = new Casilla[cols];
			}
		}
		cellHeight = sdlutils().height() / rows;
		cellWidth = sdlutils().width() / cols;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				auto* casilla = entity_->getMngr()->addEntity();
				casilla->addComponent<Transform>(Vector2D(j * cellWidth, i * cellHeight), cellWidth, cellHeight);

				file >> type;
				switch (type) {
				case 0: // Base
					casilla->addComponent<Image>(&sdlutils().images().at("tileset"), 1, 4, 0, 0);
					cells[i][j].color = Color::Ninguno;
					cells[i][j].casilla = TipoCasilla::Base;
					break;
				case 1: // Roca
					casilla->addComponent<Image>(&sdlutils().images().at("tileset"), 1, 4, 0, 3);
					cells[i][j].color = Color::Ninguno;
					cells[i][j].casilla = TipoCasilla::Pintable;
					break;
				case 2: // Agua
					casilla->addComponent<Image>(&sdlutils().images().at("tileset"), 1, 4, 0, 1);
					cells[i][j].color = Color::Ninguno;
					cells[i][j].casilla = TipoCasilla::NoPintable;
					break;
				case 3: // Cesped
					casilla->addComponent<Image>(&sdlutils().images().at("tileset"), 1, 4, 0, 2);
					cells[i][j].color = Color::Ninguno;
					cells[i][j].casilla = TipoCasilla::Pintable;
					break;
				}

				cells[i][j].character = nullptr;
			}
		}
	}
	file.close();

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

void GameMap::setColor(Vector2D cas, Color color) {
	if (getColor(cas) != color && cells[(int)cas.getY()][(int)cas.getX()].casilla == Pintable) {

		auto* pintar = entity_->getMngr()->addEntity();
		cout << cas.getX() << " " << cas.getY() << endl;
		pintar->addComponent<Transform>(Vector2D(cas.getX(), cas.getY()), cellWidth, cellHeight);
		pintar->addComponent<Image>(&sdlutils().images().at("star"));

		cells[(int)cas.getY()][(int)cas.getX()].color = color;
		cout << "Color: " << getColor(cas) << endl;
	}
}

bool GameMap::movimientoPosible(Vector2D cas) {
	return (cells[(int)cas.getY()][(int)cas.getX()].casilla != NoPintable);
}


Color GameMap::getColor(Vector2D cas) {
	return cells[(int)cas.getY()][(int)cas.getX()].color;
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