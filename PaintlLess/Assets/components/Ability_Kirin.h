#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Movimiento.h"

class Ability_Kirin : public Component {
public:
    Ability_Kirin() : tr(nullptr), mapa(nullptr) {}
    virtual ~Ability_Kirin() {}

    void init() override;
    void render() override;
    void update() override;

    void AbilityShader();
    void freeAbilityShader() { casillas.clear(); }
    bool posibleMov(Vector2D pos);

private:
    Transform* tr;
    Texture* tex;
    GameMap* mapa;
    Vector2D posKir;
    std::vector<Vector2D> casillas;
    int cellWidth = 0, cellHeight = 0;
    bool selected;
};
