#pragma once
#include "AbilityStruct.h"
#include "../components/Ability.h"

AbilityStruct::AbilityStruct(selectorColor selector, ShaderForm form, ShaderType type, int distance) :
	self(nullptr), selector(selector), shaderForm(form), shaderType(type), distance(distance) {}

void AbilityStruct::initiliceData(Ability* ab) 
{
	self = ab;
}
Ability* AbilityStruct::getAbility()
{
	return self;
}

void AbilityStruct::OnDie(){}
void AbilityStruct::AbilityExecute(int x, int y){}
void AbilityStruct::finTurno(){}

