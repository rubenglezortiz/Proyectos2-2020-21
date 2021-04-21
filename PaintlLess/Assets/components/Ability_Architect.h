#pragma once

#include "./Ability.h"
#include "../sdlutils/InputHandler.h"
#include "Movimiento.h"
#include "Health.h"

class Ability_Architect : public Ability {
public:
	Ability_Architect() : Ability(selector, generateWall), dest(SDL_Rect()),
		posArc(Vector2D()), resultado(0), selected(false) {}
	virtual ~Ability_Architect() {}

	//void init() override; //no soy capaz de meter el init en la superclase
	/*void update() override;*/

	static void generateWall(int x, int y, GameMap* map, Manager* manager);
private:
	SDL_Rect dest;
	Vector2D posArc;
	int resultado;
	bool selected;
	std::vector<Vector2D> casillasHabilidad;

	//cuando se metan margenes hay que tener cuidadd y sumarlos
};
