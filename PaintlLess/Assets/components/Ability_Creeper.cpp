#include "Ability_Creeper.h"

void Ability_Creeper::init() {
	tr_ = entity_->getComponent<Transform>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
}

void Ability_Creeper::finTurno()
{
	cout << "LFC: "<< lifeCreeper << endl;
	lifeCreeper -= 1;
	if (lifeCreeper < 0)
		entity_->setActive(false);
	else {
		auto* e = mapa->getCharacter(mapa->SDLPointToMapCoords(tr_->getPos()));	
		if (e != nullptr && equip == 0 && e->hasGroup<Equipo_Azul>() || equip == 1 && e->hasGroup<Equipo_Rojo>()) {
			e->getComponent<Health>()->hit(1);
		}					
	}
}		