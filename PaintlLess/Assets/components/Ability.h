#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "./Transform.h"
#include "../sdlutils/InputHandler.h"
#include<vector>
#include <functional>

//typedef void (*AbilityFunction)(int x, int y);
using AbilityFunction = void(int x, int y, GameMap* map, Manager* manager);
//typedef std::function<void(int, int)> AbilityFunction;

enum ShaderType { AttackSh, DefenseSh };
enum ShaderForm { Cross, TxT, Viking };

class Ability : public Component {
public:
	Ability(AbilityFunction* a) : abilityFunction(a) {}
	virtual ~Ability() {}

	virtual void init();
	virtual void render();
	virtual void update()=0;

	void AbilityShader(ShaderType st, ShaderForm sf, int d = 1);
	void freeAbilityShader();
	bool abilityCheck(const Vector2D& pos); //comprueba si en el segundo clic se est� clicando 
											//en una casilla donde se puede colocar la habilidad

protected:
	std::vector<Vector2D> abilityCells;
	Transform* characterTr; //�lo necesitan todas las habilidades?
	Texture* tex;
	GameMap* map; //NULL
	bool selected;
	int cellWidth , cellHeight;

	AbilityFunction* abilityFunction;

	void setAf(AbilityFunction* a);
	//virtual AbilityFunction(int x, int y) = 0;
};