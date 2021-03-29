// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "GameMap.h"


class MovementShader : public Component {



public:

	struct CasillaMov {
		bool checked;
		bool movPosible;
	};

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

	void casillasPosiblesRecu(const Vector2D& cSelected, vector<vector<CasillaMov>>& casillasChecked) {
		
		int casillasAMover = 3;
		//matriz igual que el tablero inicializada a false
		
		casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX(), cSelected.getY() + 1), casillasChecked, false);
		casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX() + 1, cSelected.getY()), casillasChecked, false);
		casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX(), cSelected.getY() - 1), casillasChecked, false);
		casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX() - 1, cSelected.getY()), casillasChecked, false);

		//para no volver a acceder a la inicial
		casillasChecked[cSelected.getX()][cSelected.getY()].checked = true;

		//if (!(cSelected.getX() == 0 && cActual.getX() != 0))

	}


	void casillasPosiblesRecuAux(int casillasAMover, const Vector2D& cSelected, const Vector2D& cActual, vector<vector<CasillaMov>>& casillasChecked, bool base) {

		//si se ha qeudado sin movimiento se devuelve la llamada
		if (casillasAMover == 0) return;
		
		//si la casilla está fuera del mapa no hago nada
		if (cActual.getX() < 0 || cActual.getX() >= mapa->getColumns() ||
			cActual.getY() < 0 || cActual.getY() >= mapa->getRows()) return;

		bool estaEnBase = false;
		int suma = -1;
		if (cSelected.getX() == 0 ) {

			if(base && cActual.getX() == 0){
				suma = 0;
			}
			estaEnBase = true;
		}
		//si la casilla a la que accedo no ha sido visitada
		if (!casillasChecked[cActual.getX()][cActual.getY()].checked &&
			mapa->movimientoPosible(Vector2D(cActual.getX(),cActual.getY()))) {

			if (!(cSelected.getX() == 0 && cActual.getX() != 0)) casillasChecked[cActual.getX()][cActual.getY()].checked = true;

				casillasAPintar.push_back(Vector2D(cActual.getX(), cActual.getY()));
				casillasChecked[cActual.getX()][cActual.getY()].movPosible = true;
				

				casillasPosiblesRecuAux(casillasAMover + suma, cSelected, Vector2D(cActual.getX(), cActual.getY() + 1), casillasChecked, estaEnBase);
				casillasPosiblesRecuAux(casillasAMover + suma, cSelected, Vector2D(cActual.getX() + 1, cActual.getY()), casillasChecked, estaEnBase);
				casillasPosiblesRecuAux(casillasAMover + suma, cSelected, Vector2D(cActual.getX(), cActual.getY() - 1), casillasChecked, estaEnBase);
				casillasPosiblesRecuAux(casillasAMover + suma, cSelected, Vector2D(cActual.getX() - 1, cActual.getY()), casillasChecked, estaEnBase);
			
			

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
	vector<Vector2D> casillasAPintar;//guarda las posiciones de las casillas a las que se puede mover en un vector para el render

	//cuando se metan margenes hay que tener cuidadd y sumarlos
	int cellWidth = 0, cellHeight = 0;


	Vector2D position;
	Texture* tex_;
	SDL_Rect src_;
};

