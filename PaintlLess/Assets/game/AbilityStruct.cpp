#pragma once
#include "AbilityStruct.h"

void AbilityStruct::setSelf(Ability* ab) {self = ab;}
Ability* AbilityStruct::getSelf()
{
	return self;
}
void AbilityStruct::AbilityExecute(int x, int y)
{
	if (abFunction != nullptr)abFunction(x, y, this);
	else std::cout << "PUTA MADRE\n";
}
void AbilityStruct::setAbFunction(AbilityStructFunction* abFunction)
{
	this->abFunction = abFunction;
}
;
