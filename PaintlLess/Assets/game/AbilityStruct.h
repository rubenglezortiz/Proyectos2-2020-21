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
	AbilityStruct(selectorColor selector, ShaderForm form, ShaderType type);
	AbilityStruct() :self(nullptr) {}
	selectorColor selector;
	ShaderForm  shaderForm;
	ShaderType shaderType;
	
	Ability* getAbility();
	void initiliceData(Ability* ab);
	virtual void AbilityExecute(int x, int y);
	virtual void finTurno() {};
protected:
	Ability* self;
	void setAbility(AbilityStructFunction abFunction);
private:
	AbilityStructFunction abFunction;
};

