#pragma once

#include "../ecs/Component.h"
#include "./Image.h"
#include "../ecs/Entity.h"
#include "../components/Ability_Bomb.h"
#include "../components//Ability_Golem.h"


class Health : public Component { //lleva este componente la destrucci�n del objeto??
public:
    Health(int l) : lives(l), tr(nullptr), mapa(nullptr), tex(&sdlutils().images().at("life")) {}
    virtual ~Health() {}

    void init() override;
    void render() override;
    void hit(int damage);
    void heal(int healing);
    //void setLives();

private:
    GameMap* mapa;
    Transform* tr;
    Texture* tex;
    int lives;
};