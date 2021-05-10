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
	Transform2* tr_;
	GameMap* mapa;
	Texture* tex;
	PlayState* playState;
	vector<Vector2D> casillasSpawn;
	int cellWidth, cellHeight;
	int personaje;
	bool selected = false;
	Equipo turno;
	int cool0, cool1;

	bool isSpawnable()const;
public:
	DeckSpawn(int pj) :
		personaje(pj), mapa(nullptr), tex(nullptr), playState(nullptr), cellWidth(0), cellHeight(0),
		selected(false), turno(Equipo()), cool0(0), cool1(0)
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
	void animation(Entity* character, string tex, int d, Unit p);

	void createCharacter(int character, int equipo, Vector2D posClick);
	bool spawneableCell(Vector2D pos);

	virtual void finTurno();

};