#include "Ability_Tank.h"
#include "../ecs/Entity.h"
#include "Tanque.h"

void Ability_Tank::tankPassive(AbilityStruct* info) {
	Entity* entity_ = info->getAbility()->getEntity();
	Health* mLive = entity_->getComponent<Health>();
	TanqueA* tanque = entity_->getComponent<TanqueA>();

	if (mLive->getLives() < tanque->lastVida) {
		if (tanque->turnoActual == 0) {
			mLive->heal();
			tanque->turnoActual = tanque->maxTurnos;
		}
		else {
			tanque->turnoActual--;
		}
	}
	else
		tanque->turnoActual = tanque->maxTurnos;

	std::cout << "Informe 2: \n";
	std::cout << "Turnos: " << tanque->turnoActual << "\n";
	std::cout << "Turnos Max: " << tanque->maxTurnos << "\n";
	std::cout << "Vida: " << mLive->getLives() << "\n";
	std::cout << "Objeto: " << this << "\n";
}

Ability_Tank::Ability_Tank()
{
	setOnFinTurno([&](AbilityStruct* info)
		{
			this->tankPassive(info);
		});

	setOnInit([&](AbilityStruct* info)
		{
			this->init(info);
		});

}

void Ability_Tank::init(AbilityStruct* info) {
	Entity* entity_ = info->getAbility()->getEntity();
	entity_->addComponent<TanqueA>(0, 4, 4);
}