#include "GameMap.h"
#include <iostream>
#include <fstream>
#include "..\Assets\game\Game.h"

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
		cells = new MapCell * [rows];
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				cells[r] = new MapCell[cols];
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
				case 0:
					casilla->addComponent<Image>(&sdlutils().images().at("tennis_ball"));
					cells[i][j] = Grass;
					break;
				case 1:
					casilla->addComponent<Image>(&sdlutils().images().at("star"));
					cells[i][j] = Dirt;
					break;
				case 2:
					casilla->addComponent<Image>(&sdlutils().images().at("fighter"));
					cells[i][j] = Tree;
					break;
				case 3:
					casilla->addComponent<Rectangle>(build_sdlcolor(0x112233ff));
					cells[i][j] = Rock;
					break;
				}
			}
		}
	}
	file.close();

}
void GameMap::render() {
	SDL_Rect desRect;

	desRect.h = sdlutils().height();
	desRect.w = sdlutils().width();
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			desRect.x = c * desRect.w;
			desRect.y = r * desRect.h;

		}
	}
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