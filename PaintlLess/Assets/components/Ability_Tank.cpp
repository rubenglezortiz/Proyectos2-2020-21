#include "Ability_Tank.h"
#include "../ecs/Entity.h"

Ability_Tank::Ability_Tank() : lives(0), mTurno(0), turnos(4)
{
	setOnFinTurno([this](AbilityStruct* info)
		{
			this->tankPassive(info);
		});

	setOnInit([&this](AbilityStruct* info)
		{
			this->init(info);
		});
}

void Ability_Tank::init(AbilityStruct* info) {
	Entity* entity_ = info->getAbility()->getEntity();
	Health* mLive = entity_->getComponent<Health>();
	lives = mLive->getLives();
	mTurno = turnos;
}

void Ability_Tank::tankPassive(AbilityStruct* info) {

	Entity* entity_ = info->getAbility()->getEntity();
	Health* mLive = entity_->getComponent<Health>();

	if (mLive->getLives() < lives) {
		if (mTurno == 0) {
			mLive->heal();
			mTurno = turnos;
		}
		else {
			mTurno--;
		}
	}
	else
		mTurno = turnos;

	std::cout << "Informe: \n";
	std::cout << "Turnos: " << mTurno << "\n";
	std::cout << "Turnos Max: " << turnos << "\n";
	std::cout << "Vida: " << mLive->getLives() << "\n";
}