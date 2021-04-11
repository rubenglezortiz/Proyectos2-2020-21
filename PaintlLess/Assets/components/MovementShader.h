// This file is part of the course TPV2@UCM - Samir Genaim
#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "GameMap.h"
#include "../game/Values.h"
#include "../sdlutils/InputHandler.h"

class MovementShader : public Component {
public:
	struct CasillaMov {
		bool checked;
		bool movPosible;
	};

	MovementShader(Texture* tex);
	virtual ~MovementShader() {}

	void init() override;
	void update() override;
	//método recursivo que se llama en movimiento cuando se selecciona una casilla para comprobar a que casillas se puede mover

	void casillasPosiblesRecu(const Vector2D& cSelected, vector<vector<CasillaMov>>& casillasChecked);
	void casillasPosiblesRecuAux(int casillasAMover, const Vector2D& cSelected, const Vector2D& cActual, vector<vector<CasillaMov>>& casillasChecked, bool base);
	void render() override;
	void freeCasillasAPintar();

private:
	int cont;
	SDL_Rect dest;
	GameMap* mapa;
	int resultado;
	//guarda las posiciones de las casillas a las que se puede mover en un vector para el render 
	//cuando se metan margenes hay que tener cuidad y sumarlos
	vector<Vector2D> casillasAPintar;		
	vector<pair<Vector2D,int>> casillasBaseRecorridas;
	int cellWidth = 0, cellHeight = 0;
	Vector2D position;
	Texture* tex_;
	SDL_Rect src_;
};

