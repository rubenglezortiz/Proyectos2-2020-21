#pragma once
#include "AbilityStruct.h"

AbilityStruct::AbilityStruct(selectorColor selector, ShaderForm form, ShaderType type) :
	self(nullptr), selector(selector), shaderForm(form), shaderType(type) {}

void AbilityStruct::initiliceData(Ability* ab) {self = ab;}
Ability* AbilityStruct::getAbility()
{
	return self;
}
void AbilityStruct::AbilityExecute(int x, int y)
{
	if (abFunction != nullptr)abFunction(x, y, this);
}
void AbilityStruct::setAbility(AbilityStructFunction* abFunction)
{
	this->abFunction = abFunction;
}
;
