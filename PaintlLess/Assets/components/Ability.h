#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "./Transform.h"
#include<vector>

typedef void (*ShaderFunc)();

enum ShaderType { AttackSh, DefenseSh };
enum ShaderForm {Cross, TxT, Viking};

class Ability : public Component {
protected:
	Ability() {}
	virtual ~Ability() {}

	virtual void init();
	virtual void render() {};
	virtual void update() {};

	void AbilityShader(ShaderType st, ShaderForm sf, int d=1);
	void freeAbilityShader();


	std::vector<Vector2D> abilityCells;
	Transform* characterTr; //¿lo necesitan todas las habilidades?
	Texture* tex;
	GameMap* map; //NULL
	bool selected;
};