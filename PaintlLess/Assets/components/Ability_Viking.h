#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "./Health.h"
#include "./Movimiento.h"

class Ability_Viking : public Component {
public:
	Ability_Viking() :tex(nullptr), mapa(nullptr), dest(SDL_Rect()),
		posVik(Vector2D()), selected(false) {}
	virtual ~Ability_Viking() {}

	void init() override;
	void render() override;
	void update() override;
	void AbilityShader();
	void freeAbilityShader();
	void generateWall(int x, int y);
	bool esConstruible(const Vector2D& cas);

private:
	Movimiento* mov;
	Texture* tex;
	GameMap* mapa;
	SDL_Rect dest;
	Vector2D posVik;
	int resultado;
	bool selected;
	std::vector<Vector2D> casillasHabilidad;
	//cuando se metan margenes hay que tener cuidadd y sumarlos
	int cellWidth = 0, cellHeight = 0;
	float size = 0;
};
