#pragma once

#include "../ecs/Component.h"
#include "./Image.h"
#include "../ecs/Entity.h"


class Health : public Component { //lleva este componente la destrucción del objeto??
public:
	Health(int l): lives(l), mapa(nullptr){}
	virtual ~Health() {}

	void init()override;
	void hit();
	void setLives();

private:
	GameMap* mapa;
	int lives;
};

