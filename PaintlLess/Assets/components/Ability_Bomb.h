#pragma once

#include "../game/AbilityStruct.h"
#include "Health.h"
#include "Image.h"
#include "Transform.h"
#include "Movimiento.h"

class Ability_Bomb : public AbilityStruct { //lleva este componente la destrucci�n del objeto??
public:
    Ability_Bomb();
    virtual ~Ability_Bomb() {}
};
