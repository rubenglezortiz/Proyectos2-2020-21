#pragma once

#include "./Ability.h"
#include "../ecs/Entity.h"
#include "Health.h"
#include "Image.h"
#include "Transform.h"
#include "Movimiento.h"
#include "GameMap.h"

class Ability_Golem : public Ability { //lleva este componente la destrucci�n del objeto??
public:
    Ability_Golem() {}
    void generateWall();
    
private:
};