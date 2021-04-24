#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../game/PlayState.h"

class PlayState;
class DeckSpawn : public Component {

private:
	GameMap* mapa;
	Texture* tex;
	PlayState* playState;
	vector<Vector2D> casillasSpawn;
	int cellWidth, cellHeight;
	int personaje;
	bool selected = false;
	Equipo turno;
public:
	DeckSpawn(int pj) :
	personaje(pj)
	{}
	virtual ~DeckSpawn() {}

	void init() override;
	void update() override;
	void render() override;

	void spawnShader(int e);
	void freeShader();

	void health(Entity* character, int lives);
	void attack(Entity* character, int damage, string s);
	void movement(Entity* character);
	void image(Entity* character, string tex);

	void createCharacter(int character, int equipo, Vector2D posClick);
	bool spawneableCell(Vector2D pos);
};