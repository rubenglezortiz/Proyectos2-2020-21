#pragma once

#include "../ecs/Component.h"
#include "Health.h"

class Ability_Tank : public Component { //lleva este componente la destrucci�n del objeto??
public:
    Ability_Tank() : mLive(nullptr), lives(0), mTurno(0) {}
    virtual ~Ability_Tank() {}
    void init() override;
    void finTurno() override;

private:
    Health* mLive;
    const int turnos = 4;
    int mTurno;
    int lives;
};
