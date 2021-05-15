#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "./Transform.h"
#include<vector>
#include "../sdlutils/InputHandler.h"
#include "Movimiento.h"


using AbilityFunction = void(int x, int y, GameMap* map, Manager* manager);

enum ShaderType { nullSh,AttackSh, DefenseSh, HealingSh, KirinSh, DruidaSh };
enum ShaderForm { Cross, TxT, VikingForm, ShaderWolf };

enum selectorColor { selector, selectorA, selectorH };

class Ability : public Component {
public:
	Ability() : characterTr(nullptr), tex(nullptr), map(nullptr), selected(false), cellWidth(0), cellHeight(0), form(form), type(type), shaderDistance(1){}
	Ability(selectorColor s, ShaderForm form, ShaderType type) : characterTr(nullptr), tex(nullptr), map(nullptr),
		sel(s), selected(false), cellWidth(0), cellHeight(0), form(form), type(type), shaderDistance(1) { }
	
	virtual ~Ability() {}

	virtual void init();
	virtual void render();
	virtual void update() ;
	virtual void finTurno() override;

	void AbilityShader(ShaderForm sf, ShaderType st=nullSh, int d = 1);
	void freeAbilityShader();
	virtual bool abilityCheck(const Vector2D& pos); //comprueba si en el segundo clic se está clicando 
											//en una casilla donde se puede colocar la habilidad
	bool ability_usable = true;

protected:
	ShaderForm form;
	ShaderType type;
	std::vector<Vector2D> abilityCells;
	Transform* characterTr; //¿lo necesitan todas las habilidades?
	Texture* tex;
	GameMap* map;
	selectorColor sel;
	bool selected;
	int cellWidth, cellHeight;
	int shaderDistance;
	virtual void AbilityExecute(int x, int y) {};
	PlayState* playState = nullptr;
	void SetShaderDistance(int distance) { shaderDistance = distance; };

	float lerpTime = 0;
	int casillasRendered = 0;
	float delayTime = 0;
};