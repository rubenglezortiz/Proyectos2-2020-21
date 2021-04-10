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

	Movimiento() : tr_(nullptr), mapa(nullptr), selected(false) {}

	virtual ~Movimiento() {};

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
		cellWidth = mapa->getCellWidth();
		cellHeight = mapa->getCellHeight();
		movShader = entity_->getMngr()->getHandler<BoardManager>()->getComponent<MovementShader>();
		initializeCasillasChecked();
		mapa->setCharacter(mapa->SDLPointToMapCoords(tr_->getPos()), entity_);

		assert(tr_ != nullptr);
	}

	//void render() override;

	void update() override {
		auto& pos = tr_->getPos();

		//poner el puntero de entidad de la casilla del mapa a NULL


		if (ih().getMouseButtonState(ih().LEFT)) {
			int mX = ih().getMousePos().first;
			int mY = ih().getMousePos().second;
			if (selected) {
				//esto se debe hacer en movementshader
				Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));
				if (casillasChecked[posMovimiento.getX()][posMovimiento.getY()].movPosible) {
					mapa->removeCharacter(mapa->SDLPointToMapCoords(pos));
					pos.setX(posMovimiento.getX() * cellWidth);
					pos.setY(posMovimiento.getY() * cellHeight);
					mapa->setCharacter(mapa->SDLPointToMapCoords(pos), entity_);
				}
				selected = false;

				mapa->setColor(mapa->SDLPointToMapCoords(pos), Amarillo);

				//estos métodos son para cuando se deselcciona yuna casilla para restablecer los valores de los vectores...
				movShader->freeCasillasAPintar();
				resetCasillasChecked();
			}
			else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
				selected = true;
				movShader->casillasPosiblesRecu(mapa->SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY())), casillasChecked);

			}
		}
		if (ih().getMouseButtonState(ih().RIGHT)) {
			selected = false;
			resetCasillasChecked();
			movShader->freeCasillasAPintar();
		}


	}

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
	int cellWidth = 0, cellHeight = 0;

	void initializeCasillasChecked() {
		//ese método es porque no sabemos inicializar el vector y daba errores UwU
		vector<vector<MovementShader::CasillaMov>> casillasCheckedAux(mapa->getColumns(), vector<MovementShader::CasillaMov>(mapa->getRows(), { false, false }));;
		casillasChecked = casillasCheckedAux;
	}

	void resetCasillasChecked() {
		for (int x = 0; x < mapa->getColumns(); x++) {
			for (int y = 0; y < mapa->getRows(); y++) {
				casillasChecked[x][y].checked = false;
				casillasChecked[x][y].movPosible = false;
			}
		}
	}
};

