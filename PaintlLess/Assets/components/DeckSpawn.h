#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

#include "../game/PlayState.h"

class DeckSpawn : public Component {

private:
	GameMap* mapa;
public:
	DeckSpawn() {}
	virtual ~DeckSpawn() {}
	void init() override;
	void createCharacter(int character, int equipo);

};