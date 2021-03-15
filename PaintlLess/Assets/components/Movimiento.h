#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "./Transform.h"

class Movimiento : public Component {
public:

	Movimiento() : tr_(nullptr), selected(false) {}

	virtual ~Movimiento() {};

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	//void render() override;

	void update() override {
		auto& pos = tr_->getPos();
		auto w = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>()->getCellWidth();
		auto h = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>()->getCellHeight();
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;


		if (ih().mouseButtonEvent() && selected) {
			if (ih().getMouseButtonState(ih().LEFT)) {
				if (mX > pos.getX() && mX < pos.getX() + w && mY > pos.getY() - h && mY < pos.getY() - 1) {
					pos.setY(pos.getY() - h);
				}
				else if (mX > pos.getX() && mX < pos.getX() + w && mY > pos.getY() + h && mY < pos.getY() + h * 2) {
					pos.setY(pos.getY() + h);
				}
				else if (mX > pos.getX() - w && mX < pos.getX() && mY > pos.getY() && mY < pos.getY() + h) {
					pos.setX(pos.getX() - w);
				}
				else if (mX > pos.getX() + w && mX < pos.getX() + w * 2 && mY > pos.getY() && mY < pos.getY() + h) {
					pos.setX(pos.getX() + w);
				}

				selected = false;
			}
		}

		if (ih().mouseButtonEvent() && mX > pos.getX() && mX < pos.getX() + w && mY > pos.getY() && mY < pos.getY() + h) {
			if (ih().getMouseButtonState(ih().LEFT)) {
				selected = true;
			}
		}
	}

private:
	Transform* tr_;
	bool selected;
};

