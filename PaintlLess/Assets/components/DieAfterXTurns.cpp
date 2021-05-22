#include "DieAfterXTurns.h"
#include "../ecs/Entity.h"
#include "FramedImage.h"

void DieAfterXTurns::finTurno()
{
	turnsToDie--;
	if (turnsToDie <= 0)
	{
		mapa->removeCharacter(mapa->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos())); //Quitar la entidad muerta	
		this->entity_->getComponent<FramedImage>()->setAnim(DeathA, true);
	}
}