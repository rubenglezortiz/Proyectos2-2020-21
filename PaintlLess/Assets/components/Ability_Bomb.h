#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Health.h"
#include "Image.h"
#include "Transform.h"
#include "Movimiento.h"

class Ability_Bomb : public Component { //lleva este componente la destrucci�n del objeto??
public:
    Ability_Bomb() : mapa(nullptr) {}
    virtual ~Ability_Bomb() {}
    void init() override;
    void explode();

private:
    GameMap* mapa;
    std::vector<Vector2D> casillas{ {0, -1}, {-1, -1}, {1, -1}, {1, 0}, {-1, 0}, {0, 1}, {-1, 1}, {1, 1} };
};
