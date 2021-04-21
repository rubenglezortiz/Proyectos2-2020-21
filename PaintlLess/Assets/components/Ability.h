#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "./Transform.h"
#include<vector>

typedef void (*ShaderFunc)();

enum ShaderType { nullSh,AttackSh, DefenseSh, HealingSh, KirinSh };
enum ShaderForm { Cross, TxT, VikingForm };

enum selectorColor { selector, selectorA, selectorH };

class Ability : public Component {
public:
	Ability(selectorColor s) : characterTr(nullptr), tex(nullptr), map(nullptr),
		sel(s), selected(false), cellWidth(0), cellHeight(0) {}
	virtual ~Ability() {}

	virtual void init();
	virtual void render();
	virtual void update() = 0;

	void AbilityShader(ShaderForm sf, ShaderType st=nullSh, int d = 1);
	void freeAbilityShader();
	bool abilityCheck(const Vector2D& pos); //comprueba si en el segundo clic se está clicando 
											//en una casilla donde se puede colocar la habilidad

protected:
	std::vector<Vector2D> abilityCells;
	Transform* characterTr; //¿lo necesitan todas las habilidades?
	Texture* tex;
	GameMap* map; //NULL
	selectorColor sel;
	bool selected;
	int cellWidth, cellHeight;
};