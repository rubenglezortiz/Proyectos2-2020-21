#pragma once

#include "../ecs/Component.h"
#include "./Image.h"
#include "../ecs/Entity.h"


class Health : public Component { //lleva este componente la destrucción del objeto??
public:
	Health(int l, Transform* ptr): lives(l), piece(ptr)
	{
	}

	virtual ~Health() {
	}

	void init()override {
		setLives();
	}

	void update() override {

	}

	void hit() {
		lives--;
		if (lives == 0) entity_->setActive(false);
	}

	void setLives() {
		for (int i = 0; i < lives; ++i) {
			auto l = entity_->getMngr()->addEntity();			
			Vector2D pos = Vector2D(1,/*piece->getPos().getX() + piece->getW() - 5 * i*/1);


			l->addComponent<Transform>(pos, 50.0f, 500.0f);
			l->getComponent<Transform>()->setH(25.0);
			l->getComponent<Transform>()->setW(25.0);
			l->addComponent<Image>(&sdlutils().images().at("life"));
		
		}
	}

private:
	int lives;
	Transform* piece; //transform del personaje
};

