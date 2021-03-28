// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "GameMap.h"


class MovementShader : public Component {
public:
	MovementShader(Texture* tex) :
		tex_(tex) //
	{
		cont = 0;

	}

	virtual ~MovementShader() {
	}

	void getValues() {
		cellWidth = mapa->getCellWidth();
		cellHeight = mapa->getCellHeight();
	}

	void update() override {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;

		if (sdlutils().currRealTime() > cont + 10) {


			resultado = mX / mapa->getCellWidth();
			dest.x = resultado *  mapa->getCellWidth();
			resultado = mY / mapa->getCellHeight();
			dest.y = resultado *  mapa->getCellHeight();
			

			
			cont = sdlutils().currRealTime();
		}

	}

	//método recursivo que se llama en movimiento cuando se selecciona una casilla para comprobar a que casillas se puede mover

	void casillasPosiblesRecu(const Vector2D& cSelected/*, vector<coorCasilla>& casillasChecked*/) {

		casillasAPintar.push_back(Vector2D(cSelected.getX(), cSelected.getY() + 1));
		casillasAPintar.push_back(Vector2D(cSelected.getX() + 1, cSelected.getY()));
		casillasAPintar.push_back(Vector2D(cSelected.getX(), cSelected.getY() - 1));
		casillasAPintar.push_back(Vector2D(cSelected.getX() - 1, cSelected.getY()));
	

	}
	void render() override
	{
		SDL_Rect dest;


		for (Vector2D casilla : casillasAPintar) {
			dest.x = casilla.getX()/* * cellWidth*/ /*+ offset*/;
			dest.y = casilla.getY() /** cellHeight *//*+ offset*/;
			dest.h = cellHeight;
			dest.w = cellWidth;

			tex_->render(dest);
		}
	}


private:
	int cont;
	SDL_Rect dest;
	GameMap* mapa;
	int resultado;
	vector<Vector2D> casillasAPintar;

	//cuando se metan margenes hay que tener cuidadd y sumarlos
	int cellWidth = 0, cellHeight = 0;


	Vector2D position;
	Texture* tex_;
	SDL_Rect src_;
};

