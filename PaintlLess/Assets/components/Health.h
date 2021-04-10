#pragma once

#include "../ecs/Component.h"
#include "./Image.h"
#include "../ecs/Entity.h"
#include "../components/DejaMuro.h"


class Health : public Component { //lleva este componente la destrucción del objeto??
public:
	Health(int l): lives(l), tr(nullptr), mapa(nullptr), tex(&sdlutils().images().at("life")){}
	virtual ~Health() {}

	void init() override;
	void render() override;
	void hit();
	//void setLives();

private:
	GameMap* mapa;
	Transform* tr;
	Texture* tex;
	int lives;	
};

