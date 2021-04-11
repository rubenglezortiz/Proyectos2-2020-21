#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Health.h"
#include "Image.h"
#include "Transform.h"
#include "Movimiento.h"

class Ability_Golem : public Component { //lleva este componente la destrucci�n del objeto??
public:
    Ability_Golem() : tr(nullptr), mapa(nullptr) {}

    void init() override;
    void generateWall();

private:
    Transform* tr;
    GameMap* mapa;
};