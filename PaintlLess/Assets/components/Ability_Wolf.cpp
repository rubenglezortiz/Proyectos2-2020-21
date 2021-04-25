#include "Ability_Wolf.h"


void Ability_Wolf::AbilityExecute(int x, int y)
{
	//la x e y es la casilla en la que se ha clickado pero aqui da igual, 
	//se pasan pero no se usan
	Vector2D newPos;
	for (int i = 0; i < abilityCells.size(); i++)
	{
		if (entity_->hasGroup<Equipo_Rojo>())
			newPos = Vector2D(abilityCells[i].getX() + 1, abilityCells[i].getY());
		else
			newPos = Vector2D(abilityCells[i].getX() - 1, abilityCells[i].getY());


		if (map->getCharacter(newPos) != nullptr) //Choca con character
		{
			map->getCharacter(newPos)->getComponent<Health>()->hit(1);
			map->getCharacter(abilityCells[i])->getComponent<Health>()->hit(1);
		}
		else if (!map->movimientoPosible(newPos)) //Muere instantaneo
		{
			map->getCharacter(abilityCells[i])->getComponent<Health>()->hit(10);
			sdlutils().soundEffects().at("caeraguaSound").setChunkVolume(5);
			sdlutils().soundEffects().at("caeraguaSound").play(); //-----------------------------------------------------------		
		}
		else //Se mueve
		{
			//Personaje que queremos mover
			auto& pos = map->getCharacter(abilityCells[i])->getComponent<Transform>()->getPos();
			auto* entit = map->getCharacter(abilityCells[i]);

			map->removeCharacter(map->SDLPointToMapCoords(pos));
			pos.setX((newPos.getX() * cellWidth) + OFFSET_X);
			pos.setY((newPos.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP);
			map->setCharacter(map->SDLPointToMapCoords(pos), entit);

			sdlutils().soundEffects().at("loboSound").setChunkVolume(5);
			sdlutils().soundEffects().at("loboSound").play(); //-----------------------------------------------------------					
			//Pintar suelo
			if (map->getColor(map->SDLPointToMapCoords(pos)) != Rojo && entit->hasGroup<Equipo_Rojo>())
				map->setColor(map->SDLPointToMapCoords(pos), Rojo);
			else if (map->getColor(map->SDLPointToMapCoords(pos)) != Amarillo && entit->hasGroup<Equipo_Azul>())
				map->setColor(map->SDLPointToMapCoords(pos), Amarillo);
		}
	}
}