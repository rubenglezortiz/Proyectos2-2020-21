#include "GameMap.h"
#include <iostream>
#include <fstream>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include "../game/Game.h"
#include "./PointOnImage.h"
#include "../game/PlayState.h"
#include "../game/OffsetInfo.h"

using namespace std;

GameMap::GameMap(int level, int tileSet, PlayState* playState) : playState(playState), level(level), tileSet(tileSet) {}

GameMap::~GameMap() {
	for (int r = 0; r < rows; ++r)
		delete[] cells[r];
	delete[] cells;
}

void GameMap::init() {
	loadMap();
}
void GameMap::loadMap() {
	tmx::Map map;
	if (map.load(sdlutils().tiled().at("mapa" + to_string(level)))) {
		const auto& layers = map.getLayers();
		for (const auto& layer : layers) {
			if (layer->getType() == tmx::Layer::Type::Tile) {
				const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();

				cols = tileLayer.getSize().x; rows = tileLayer.getSize().y;
				cells = new Casilla * [rows];
				for (int r = 0; r < rows; ++r) {
					for (int c = 0; c < cols; ++c) {
						cells[r] = new Casilla[cols];
					}
				}

				int alto = sdlutils().height() - OFFSET_Y * 2;
				int ancho = sdlutils().width() - OFFSET_X * 2;
				cellWidth = ancho / cols;
				cellHeight = (alto / rows);
				nCasPintables = 0;

				auto tiles = tileLayer.getTiles();
				for (int i = 0; i < rows; ++i) {
					for (int j = 0; j < cols; ++j) {
						auto* casilla = entity_->getMngr()->addEntity();

						casilla->addComponent<Transform2>(Vector2D(j * cellWidth + OFFSET_X, (i * cellHeight) + OFFSET_Y + OFFSET_TOP), cellWidth, cellHeight);
						string tileset = "tileset" + to_string(tileSet);
						int casTiled = tiles[i * cols + j].ID - 1;
						casilla->addComponent<Image>(&sdlutils().images().at(tileset), 4, 3, casTiled / 3, casTiled % 3);
						if (tileSet < 3) {
							if (casTiled < 8) {
								// Agua
								cells[i][j].color = Color::Ninguno;
								cells[i][j].tipoCasilla = TipoCasilla::NoPintable;
							}
							else if (casTiled < 10) {
								// Base
								cells[i][j].color = Color::Ninguno;
								cells[i][j].tipoCasilla = TipoCasilla::Base;
							}
							else {
								// Roca
								cells[i][j].color = Color::Ninguno;
								cells[i][j].tipoCasilla = TipoCasilla::Pintable;
								nCasPintables++;
							}
						}
						else {
							if (casTiled == 11) {
								// Agua
								cells[i][j].color = Color::Ninguno;
								cells[i][j].tipoCasilla = TipoCasilla::NoPintable;
							}
							else if(casTiled == 9){
								// Base
								cells[i][j].color = Color::Ninguno;
								cells[i][j].tipoCasilla = TipoCasilla::Base;
							}
							else {
								// Roca
								cells[i][j].color = Color::Ninguno;
								cells[i][j].tipoCasilla = TipoCasilla::Pintable;
								nCasPintables++;
							}
						}
						cells[i][j].character = nullptr;
						cells[i][j].obstaculo = nullptr;
					}
				}
			}
		}
	}
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
	if (cells[(int)cas.getY()][(int)cas.getX()].tipoCasilla == Pintable) {
		auto* pintar = entity_->getMngr()->addEntity(RenderLayer::Tablero);
		pintar->addComponent<Transform>(Vector2D(cas.getX(), cas.getY()), cellWidth, cellHeight);
		if (getColor(cas) != color && getColor(cas) != Ninguno && color == Amarillo) {
			pintar->addComponent<Image>(&sdlutils().images().at("rojo"));
			playState->aumentaPintado1(1);
			playState->aumentaPintado2(-1);
		}
		else if (getColor(cas) != color && getColor(cas) != Ninguno && color == Rojo) {
			pintar->addComponent<Image>(&sdlutils().images().at("azul"));
			playState->aumentaPintado2(1);
			playState->aumentaPintado1(-1);
		}
		else if (getColor(cas) == Ninguno) {
			if (color == Amarillo) {
				pintar->addComponent<Image>(&sdlutils().images().at("rojo"));
				playState->aumentaPintado1(1);
			}
			else {
				pintar->addComponent<Image>(&sdlutils().images().at("azul"));
				playState->aumentaPintado2(1);
			}
		}

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

void GameMap::setObstaculo(const Vector2D& cas, Entity* e) {
	cells[(int)cas.getY()][(int)cas.getX()].obstaculo = e;
}

void GameMap::removeCharacter(const Vector2D& cas) {
	cells[(int)cas.getY()][(int)cas.getX()].character = nullptr;
}

void GameMap::removeObstaculo(const Vector2D& cas) {
	cells[(int)cas.getY()][(int)cas.getX()].obstaculo = nullptr;
}

// Salta excepción al no encontrar 4 casillas en el borde inferior.


Color GameMap::getColor(Vector2D cas) {
	return cells[(int)cas.getY()][(int)cas.getX()].color;
}

bool GameMap::casillaValida(const Vector2D& cas) //SUPONEMOS QUE ESTÁ BIEN, ACEPTAMOS CAMBIOS XDD
{
	return cas.getX() >= 0 && cas.getX() < getColumns() && cas.getY() >= 0 && cas.getY() < getRows();
}


bool GameMap::movimientoPosible(const Vector2D& cas) {
	if (!casillaValida(cas))return false;
	int x = cas.getX(); int y = cas.getY();
	return (cells[y][x].tipoCasilla != NoPintable && cells[y][x].character == nullptr && cells[y][x].obstaculo == nullptr);
}

bool GameMap::movimientoPosibleEnredadera(const Vector2D& cas) {
	if (!casillaValida(cas))return false;
	int x = cas.getX(); int y = cas.getY();
	if (cells[y][x].character != nullptr && cells[y][x].obstaculo == nullptr)
		return ((cells[y][x].character->hasComponent<Movimiento>() || cells[y][x].character->hasComponent<Attack>()) && cells[y][x].tipoCasilla != NoPintable);
	else if (cells[y][x].obstaculo == nullptr)
		return cells[y][x].tipoCasilla != NoPintable;
	else return false;
}

bool GameMap::ataquePosible(const Vector2D& cas) {
	if (!casillaValida(cas)) return false;
	int x = cas.getX(); int y = cas.getY();
	// Ha de hacer distinción entre personaje amigo y enemigo.
	if (cells[y][x].character != nullptr) {
		if (playState->getTurno() == Primero)
			return !cells[y][x].character->hasGroup<Equipo_Azul>();
		else
			return !cells[y][x].character->hasGroup<Equipo_Rojo>();
	}
	else if (cells[y][x].obstaculo != nullptr) {
		if (playState->getTurno() == Primero)
			return !cells[y][x].obstaculo->hasGroup<Equipo_Azul>();
		else
			return !cells[y][x].obstaculo->hasGroup<Equipo_Rojo>();
	}
	else return false;
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