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

		assert(tr_ != nullptr);
	}

	//void render() override;

	void update() override {
		auto& pos = tr_->getPos();
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		Vector2D nextPos = pos;


		if (ih().mouseButtonEvent() && selected) {
			if (ih().getMouseButtonState(ih().LEFT)) {
				if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() - cellHeight && mY < pos.getY() - 1) {
					nextPos.setY(pos.getY() - cellHeight);
				}
				else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() + cellHeight && mY < pos.getY() + cellHeight * 2) {
					nextPos.setY(pos.getY() + cellHeight);
				}
				else if (mX > pos.getX() - cellWidth && mX < pos.getX() && mY > pos.getY() && mY < pos.getY() + cellHeight) {
					nextPos.setX(pos.getX() - cellWidth);
				}
				else if (mX > pos.getX() + cellWidth && mX < pos.getX() + cellWidth * 2 && mY > pos.getY() && mY < pos.getY() + cellHeight) {
					nextPos.setX(pos.getX() + cellWidth);
				}

				if (mapa->movimientoPosible(SDLPointToMapCoords(nextPos))) pos = nextPos;
				selected = false;

				mapa->setColor(SDLPointToMapCoords(pos), Amarillo);
			}
		}
		else if (ih().mouseButtonEvent() && mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			if (ih().getMouseButtonState(ih().LEFT)) {
				selected = true;
				movShader->casillasPosiblesRecu(SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY())));
			}
		}

	}

	Vector2D MapCoordsToSDLPoint(Vector2D coords) const { //Pasar de coordenadas del mapa a pixeles
		Vector2D p{ (coords.getX() * cellWidth) , (coords.getY() * cellHeight)/* + DESPL*/ };
		cout << p.getX() << " " << p.getY() << endl;
		return p;
	}

	Vector2D SDLPointToMapCoords(Vector2D p) const { //Pasar de pixeles a coordenadas del mapa
		Vector2D coords{ (p.getX() / cellWidth), (p.getY()/*-DESPL*/) / cellHeight };
		cout << coords.getX() << " " << coords.getY() << endl;
		return coords;
	}

private:
	MovementShader* movShader;
	Transform* tr_;
	GameMap* mapa;
	bool selected;
	int cellWidth = 0, cellHeight = 0;
};

