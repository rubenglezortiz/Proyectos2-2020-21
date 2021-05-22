#pragma once
#include <iostream>
#include <functional>

enum ShaderType { nullSh, AttackSh, DefenseSh, HealingSh, KirinSh, DruidaSh };
enum ShaderForm { Cross, TxT, VikingForm, ShaderWolf };

enum selectorColor { selector, selectorA, selectorH };

class Ability;

class AbilityStruct
{
public:
	//using AbilityStructFunction = void(int x, int y, AbilityStruct* father);
	using AbilityStructFunction = std::function<void(int, int, AbilityStruct* father)>;
	using AbilityEvent = std::function<void(AbilityStruct* father)>;
	AbilityStruct(selectorColor selector, ShaderForm form, ShaderType type, int distance = 1);
	AbilityStruct() :self(nullptr) {}
	selectorColor selector;
	ShaderForm  shaderForm;
	ShaderType shaderType;
	int distance;
	
	Ability* getAbility();
	void OnDie();
	void initiliceData(Ability* ab);
	virtual void AbilityExecute(int x, int y);
	virtual void finTurno();
protected:
	Ability* self;
	void setAbility(AbilityStructFunction abFunction);
	void setOnDie(AbilityEvent onDie);
	void setOnFinTurno(AbilityEvent onFinTurno);
	void setOnInit(AbilityEvent onInit);
private:
	AbilityStructFunction abFunction;
	AbilityEvent onDie = nullptr;
	AbilityEvent onFinTurno = nullptr;
	AbilityEvent onInit = nullptr;
};

