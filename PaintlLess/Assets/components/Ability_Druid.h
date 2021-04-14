#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "../sdlutils/InputHandler.h"
#include "Movimiento.h"
#include "Health.h"

class PlayState;
class Ability_Druid : public Component {
public:
	Ability_Druid(PlayState* p, int e) : tex(nullptr), mapa(nullptr), dest(SDL_Rect()),
		posArc(Vector2D()), selected(false), equip(e), pSt(p) {}
	virtual ~Ability_Druid() {}

	void init() override;
	void render() override;
	void update() override;
	void finTurno() override;
	void AbilityShader();
	void freeAbilityShader();
	void generateWall(int x, int y);
	bool esConstruible(const Vector2D& cas);
private:	
	Texture* tex;
	GameMap* mapa;
	PlayState* pSt;
	SDL_Rect dest;
	Vector2D posArc;
	bool selected;
	bool habilidad = true;
	std::vector<Vector2D> casillasHabilidad;
	int equip;

	//cuando se metan margenes hay que tener cuidadd y sumarlos
	int cellWidth = 0, cellHeight = 0;
};
