#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "./MovementShader.h"

class Movimiento : public Component {
public:
	Movimiento(PlayState* playState) : tr_(nullptr), mapa(nullptr), selected(false), movShader(nullptr), cellWidth(0), cellHeight(0), playState(playState) {}
	virtual ~Movimiento() {};


	void init() override;
	void update() override;
	void finTurno() override;

	void setStun(int x) { stun = x * 2; }
	int getStun() const { return stun; }

	//Vector2D MapCoordsToSDLPoint(Vector2D coords) const { //Pasar de coordenadas del mapa a pixeles
	//	Vector2D p{ (coords.getX() * cellWidth) , (coords.getY() * cellHeight)/* + DESPL*/ };
	//	cout << p.getX() << " " << p.getY() << endl;
	//	return p;
	//}

	//Vector2D SDLPointToMapCoords(Vector2D p) const { //Pasar de pixeles a coordenadas del mapa
	//	//como las casillas neceitan int se hace aqui el casteo
	//	int X = p.getX() / cellWidth;
	//	int Y = p.getY()/*-DESPL*/ / cellHeight;
	//	//como vector2D es float se hace el casteo pero el valor va a ser .0000
	//	Vector2D coords{ (float)X,(float)Y };
	//	cout << coords.getX() << " " << coords.getY() << endl;
	//	return coords;
	//}

private:
	vector<vector<MovementShader::CasillaMov>> casillasChecked;
	MovementShader* movShader;
	Transform* tr_;
	GameMap* mapa;
	bool selected;
	int cellWidth;
	int cellHeight;
	void initializeCasillasChecked();
	void resetCasillasChecked();
	PlayState* playState = nullptr;

	int stun = false;


};