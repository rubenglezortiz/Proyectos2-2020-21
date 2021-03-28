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

	void init() override {
		mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();

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

	void casillasPosiblesRecu(const Vector2D& cSelected ) {
		
		int casillasAMover = 3;
		//matriz igual que el tablero inicializada a false
		vector<vector<bool>> casillasChecked(mapa->getRows(), vector<bool>(mapa->getColumns(), false));
		casillasPosiblesRecuAux(casillasAMover, cSelected, Vector2D(cSelected.getX(), cSelected.getY() + 1), casillasChecked);
		casillasPosiblesRecuAux(casillasAMover, cSelected, Vector2D(cSelected.getX() + 1, cSelected.getY()), casillasChecked);
		casillasPosiblesRecuAux(casillasAMover, cSelected, Vector2D(cSelected.getX(), cSelected.getY() - 1), casillasChecked);
		casillasPosiblesRecuAux(casillasAMover, cSelected, Vector2D(cSelected.getX() - 1, cSelected.getY()), casillasChecked);

		//para no volver a acceder a la inicial
		casillasChecked[cSelected.getX()][cSelected.getY()] = true;

	}


	void casillasPosiblesRecuAux(int casillasAMover, const Vector2D& cSelected, const Vector2D& cActual, vector<vector<bool>>& casillasChecked) {

		//si se ha qeudado sin movimiento se devuelve la llamada
		if (casillasAMover == 0) return;

		//si la casilla a la que accedo no ha sido visitada
		if (!casillasChecked[cActual.getX()][cActual.getY()]) {


			casillasChecked[cActual.getX()][cActual.getY()] = true;
			casillasAPintar.push_back(Vector2D(cActual.getX(), cActual.getY()));


			casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cActual.getX(), cActual.getY() + 1), casillasChecked);
			casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cActual.getX() + 1, cActual.getY()), casillasChecked);
			casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cActual.getX(), cActual.getY() - 1), casillasChecked);
			casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cActual.getX() - 1, cActual.getY()), casillasChecked);

		}
		

	}
	void render() override
	{
		SDL_Rect dest;


		for (Vector2D casilla : casillasAPintar) {
			dest.x = casilla.getX() * cellWidth /*+ offset*/;
			dest.y = casilla.getY() * cellHeight /*+ offset*/;
			dest.h = cellHeight;
			dest.w = cellWidth;

			tex_->render(dest);
		}
	}
	void freeCasillasAPintar() {
		casillasAPintar.clear();
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

