#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "./Transform.h"
#include<vector>

typedef void (*ShaderFunc)();

enum ShaderType { AttackSh, DefenseSh };
enum ShaderForm { Cross, TxT, Viking };

class Ability : public Component {
public:
	Ability() {}
	virtual ~Ability() {}

	virtual void init();
	virtual void render();
	virtual void update()=0;

	void AbilityShader(ShaderType st, ShaderForm sf, int d = 1);
	void freeAbilityShader();
	bool abilityCheck(const Vector2D& pos); //comprueba si en el segundo clic se está clicando 
											//en una casilla donde se puede colocar la habilidad

protected:
	std::vector<Vector2D> abilityCells;
	Transform* characterTr; //¿lo necesitan todas las habilidades?
	Texture* tex;
	GameMap* map; //NULL
	bool selected;
	int cellWidth , cellHeight;
};