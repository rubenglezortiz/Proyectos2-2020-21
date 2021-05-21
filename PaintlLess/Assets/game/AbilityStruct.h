#pragma once

enum ShaderType { nullSh, AttackSh, DefenseSh, HealingSh, KirinSh, DruidaSh };
enum ShaderForm { Cross, TxT, VikingForm, ShaderWolf };

enum selectorColor { selector, selectorA, selectorH };

class Ability;

struct AbilityStruct
{
public:
	AbilityStruct(selectorColor selector, ShaderForm form, ShaderType type) :self(nullptr) {}
	AbilityStruct() :self(nullptr) {}
	selectorColor selector;
	ShaderForm  shaderForm;
	ShaderType shaderType;
	void setSelf(Ability* ab);
	virtual void AbilityExecute(int x, int y) {};
	virtual void finTurno() {};

protected:
	Ability* self;
};
