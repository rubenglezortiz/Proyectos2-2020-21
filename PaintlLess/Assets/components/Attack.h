#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"

#include "Ability_Rogue.h"
#include "Health.h"

#include <vector>

/*
* Attack gestiona la habilidad de ataque básico de todos los personajes.
*/
class Attack : public Component {
private:
	bool selected;
	int cellWidth, cellHeight, range;
	Transform* tr_;
	GameMap* mapa;
	Texture* tex_;
	vector<Vector2D> casillasAtaque;

public:
	Attack(int r = 1) :
		range(r), selected(false), cellWidth(0), cellHeight(0), tr_(nullptr), mapa(nullptr), tex_(nullptr)
	{}
	~Attack() {}

	void init() override;
	void render() override;
	void update() override;
	// Método que detecta los clicks y gestiona el ataque.
	void attack();
	// Método que detecta las casillas que se pueden atacar y renderiza.
	void attackShader();
	// Método que devuelve true si en la casilla hay un personaje.
	bool canAttack(Vector2D pos);
};