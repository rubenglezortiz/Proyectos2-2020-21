#pragma once
#include <iostream>

enum ShaderType { nullSh, AttackSh, DefenseSh, HealingSh, KirinSh, DruidaSh };
enum ShaderForm { Cross, TxT, VikingForm, ShaderWolf };

enum selectorColor { selector, selectorA, selectorH };

class Ability;

class AbilityStruct
{
public:
	using AbilityStructFunction = void(int x, int y, AbilityStruct* father);
	AbilityStruct(selectorColor selector, ShaderForm form, ShaderType type) :self(nullptr) {}
	AbilityStruct() :self(nullptr) {}
	selectorColor selector;
	ShaderForm  shaderForm;
	ShaderType shaderType;
	void setSelf(Ability* ab);
	Ability* getSelf();
	virtual void AbilityExecute(int x, int y);
	virtual void finTurno() {};
protected:
	Ability* self;
	void setAbFunction(AbilityStructFunction* abFunction);
private:
	AbilityStructFunction* abFunction;
};

