#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "../sdlutils/InputHandler.h"
#include "Movimiento.h"

class Ability_Architect : public Component {
public:
	Ability_Architect() {}


	virtual ~Ability_Architect() {
	}

	void init() override {
		mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
		mov = entity_->getComponent<Movimiento>();

		cellWidth = mapa->getCellWidth();
		cellHeight = mapa->getCellHeight();

		tex = &sdlutils().images().at("selector");
	}

	void render() override {
		SDL_Rect dest;


		for (Vector2D casilla : casillasHabilidad) {
			dest.x = casilla.getX() * cellWidth /*+ offset*/;
			dest.y = casilla.getY() * cellHeight /*+ offset*/;
			dest.h = cellHeight;
			dest.w = cellWidth;

			tex->render(dest);
		}
	}

	void update() override {
		auto& pos = entity_->getComponent<Transform>()->getPos();

		Vector2D nextPos = pos;

		if (ih().getMouseButtonState(ih().RIGHT)) {
			int mX = ih().getMousePos().first;
			int mY = ih().getMousePos().second;
			if (selected) {
				if (ih().getMouseButtonState(ih().RIGHT)) { //???????
					//esto se debe hacer en movementshader
					Vector2D posMovimiento = mov->SDLPointToMapCoords(Vector2D(mX, mY));

					//if (casillasHabilidad[posMovimiento.getX()][posMovimiento.getY()]) {
					//	pos.setX(posMovimiento.getX() * cellWidth);
					//	pos.setY(posMovimiento.getY() * cellHeight);
					//}
					selected = false;
					generateWall(posMovimiento.getX(), posMovimiento.getY());

					//mapa->setColor(mov->SDLPointToMapCoords(pos), Amarillo);

					////estos métodos son para cuando se deselcciona yuna casilla para restablecer los valores de los vectores...
					//movShader->freeCasillasAPintar();
					freeAbilityShader();
					//resetCasillasChecked();
				}
			}
			else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
				if (ih().getMouseButtonState(ih().RIGHT)) { //?????
					//si la casilla está fuera del mapa no hago nada
					//if (nextPos.getX() < 0 || nextPos.getX() >= mapa->getColumns() ||
					//	nextPos.getY() < 0 || nextPos.getY() >= mapa->getRows()) return;

					selected = true;
					AbilityShader();
					//movShader->casillasPosiblesRecu(mov->SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY())), casillasChecked);
				}
			}
		}
	}

	void AbilityShader() {
		posArc = entity_->getComponent<Transform>()->getPos();

		posArc = mov->SDLPointToMapCoords(posArc);

		Vector2D posUp = Vector2D(0, 1) + posArc;
		Vector2D posRight = Vector2D(1, 0) + posArc;
		Vector2D posLeft = Vector2D(-1, 0) + posArc;
		Vector2D posDown = Vector2D(0, -1) + posArc;

		if (mapa->movimientoPosible(posUp)) casillasHabilidad.push_back(posUp);
		if (mapa->movimientoPosible(posRight)) casillasHabilidad.push_back(posRight);
		if (mapa->movimientoPosible(posLeft)) casillasHabilidad.push_back(posLeft);
		if (mapa->movimientoPosible(posDown)) casillasHabilidad.push_back(posDown);
	}

	void freeAbilityShader() {
		casillasHabilidad.clear();
	}

	void generateWall(int x, int y) {
		// x e y
		//Crea imagen
		auto* e = entity_->getMngr()->addEntity(RenderLayer::Tablero3);

		e->addComponent<Transform>(
			Vector2D(x, y), //Posicion
			Vector2D(),     //Velocidad
			50.0f,          //Ancho
			50.0f,          //Alto
			0.0f);

		e->addComponent<Image>(&sdlutils().images().at("kirin"));
		e->addComponent<Health>(2, e->getComponent<Transform>());
	}

private:
	Movimiento* mov;
	Texture* tex;
	GameMap* mapa;
	SDL_Rect dest;
	Vector2D posArc;
	int resultado;
	bool selected;
	std::vector<Vector2D> casillasHabilidad;

	//cuando se metan margenes hay que tener cuidadd y sumarlos
	int cellWidth = 0, cellHeight = 0;
};
