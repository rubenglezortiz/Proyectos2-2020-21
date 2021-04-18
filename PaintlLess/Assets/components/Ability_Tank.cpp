#include "Ability_Tank.h"
#include "../ecs/Entity.h"

void Ability_Tank::init() {
	mLive = entity_->getComponent<Health>();
	lives = mLive->getLives();
	mTurno = turnos;
}

void Ability_Tank::finTurno() {
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
}