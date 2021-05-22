#pragma once

#include "./Ability.h"
#include "../game/AbilityStruct.h"
#include "../ecs/Entity.h"
#include "Health.h"
#include "FramedImage.h"
#include "Transform.h"
#include "Attack.h"
#include "Movimiento.h"
#include "GameMap.h"

class Ability_Skeleton : public AbilityStruct {
public:
    Ability_Skeleton(int lv);
    virtual void OnDie() override;
    ~Ability_Skeleton() {};

private:
    int livesSk_;
    GameMap* mapa_;
    Transform* tr_;
    Entity* entity_;
};