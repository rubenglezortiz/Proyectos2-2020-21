#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"

#include "Ability_Rogue.h"
#include "Health.h"

#include <vector>
#include "UniversalShader.h"

/*
* Attack gestiona la habilidad de ataque b�sico de todos los personajes.
*/

class PlayState;
class GameStateMachine;
class Attack : public Component {
private:
	bool selected;
	bool ability_usable = true;
	int cellWidth, cellHeight, range;
	Transform* tr_;
	GameMap* mapa;
	vector<Vector2D> casillasAtaque;

	PlayState* playState;
	GameStateMachine* gsm;
	string sound;
	int dmg;
	int dmgCrit;
	int probCrit;

public:
	Attack(PlayState* playState, int dmg, int dmgCrit, float probCrit, string s = "ataqueSound") :
		range(1), selected(false), cellWidth(0), cellHeight(0), tr_(nullptr),
		mapa(nullptr), playState(playState), sound(s), gsm(nullptr), dmg(dmg), dmgCrit(dmgCrit), probCrit(probCrit)
	{}
	~Attack() {}

	void init() override;
	void update() override;
	void finTurno() override;
	// M�todo que detecta los clicks y gestiona el ataque.
	void attack();
	void attackDelegate(const Vector2D& cas, const int& damage);
	void attackSound();
	// M�todo que detecta las casillas que se pueden atacar y renderiza.
	void attackShader();
	// M�todo que devuelve true si en la casilla hay un personaje.
	bool canAttack(Vector2D pos);
private:
	UniversalShader* attackShader_;
};