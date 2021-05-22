#pragma once
#include "AbilityStruct.h"
#include "../components/Ability.h"

AbilityStruct::AbilityStruct(selectorColor selector, ShaderForm form, ShaderType type, int distance) :
	self(nullptr), selector(selector), shaderForm(form), shaderType(type), distance(distance) {}

void AbilityStruct::initiliceData(Ability* ab) 
{
	self = ab;
	if(onInit != nullptr)onInit(this);
}
Ability* AbilityStruct::getAbility()
{
	return self;
}

void AbilityStruct::OnDie()
{
	if (onDie != nullptr) onDie(this);
}

void AbilityStruct::AbilityExecute(int x, int y)
{
	if (abFunction != nullptr)abFunction(x, y, this);
}
void AbilityStruct::finTurno()
{
	if (onFinTurno != nullptr) onFinTurno(this);
}
void AbilityStruct::setAbility(AbilityStructFunction abFunction)
{
	this->abFunction = abFunction;
}
void AbilityStruct::setOnDie(AbilityEvent onDie)
{
	this->onDie = onDie;
}

void AbilityStruct::setOnFinTurno(AbilityEvent onFinTurno)
{
	this->onFinTurno = onFinTurno;
}

void AbilityStruct::setOnInit(AbilityEvent onInit)
{
	this->onInit = onInit;
}

