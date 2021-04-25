#include "Ability_Wolf.h"

void Ability_Wolf::init()
{
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	assert(mapa != nullptr);
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	tex = &sdlutils().images().at("selectorA");

	if (entity_->hasGroup<Equipo_Rojo>())
		casillas = { {1, 0}, {2, 0}, { 1, 1}, {2, 1}, {1, -1}, {2, -1} }; //Izquierda ==> Derecha
	else
		casillas = { {-1, 0}, {-2, 0}, {-1, 1}, {-2, 1}, {-1, -1}, {-2, -1} }; //Derecha ==> Izquierda
}

void Ability_Wolf::update()
{
	auto& pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			blow();

			selected = false;
			freeShader();
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			selected = true;
			shaderAttack();
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeShader();
	}
}

void Ability_Wolf::render()
{
	SDL_Rect dest;
	for (Vector2D casilla : shader) {
		dest.x = casilla.getX() * cellWidth + OFFSET_X;
		dest.y = casilla.getY() * cellHeight + OFFSET_Y + OFFSET_TOP;
		dest.h = cellHeight;
		dest.w = cellWidth;
		tex->render(dest);
	}
}

void Ability_Wolf::shaderAttack()
{
	posWolf = entity_->getComponent<Transform>()->getPos();

	posWolf = mapa->SDLPointToMapCoords(posWolf);

	for (int i = 0; i < casillas.size(); i++) { // 12, 2 por cada lao
		if (mapa->casillaValida(casillas[i] + posWolf)) {
			//Hay personaje en el 1
			if (mapa->getCharacter(casillas[i] + posWolf) != nullptr) {
				shader.push_back(casillas[i] + posWolf);
			}
			//Hay personaje en el 2
			else if (mapa->getCharacter(casillas[i + 1] + posWolf) != nullptr)
			{
				shader.push_back(casillas[i + 1] + posWolf);
			}	
		}	
		i++;
	}
}

void Ability_Wolf::blow()
{
	Vector2D newPos;
	for (int i = 0; i < shader.size(); i++)
	{
		if (entity_->hasGroup<Equipo_Rojo>())
			newPos = Vector2D(shader[i].getX() + 1, shader[i].getY());
		else
			newPos = Vector2D(shader[i].getX() - 1, shader[i].getY());


		if (mapa->getCharacter(newPos) != nullptr) //Choca con character
		{
			mapa->getCharacter(newPos)->getComponent<Health>()->hit(1);
			mapa->getCharacter(shader[i])->getComponent<Health>()->hit(1);
		}
		else if (!mapa->movimientoPosible(newPos)) //Muere instantaneo
		{
			mapa->getCharacter(shader[i])->getComponent<Health>()->hit(10);
			sdlutils().soundEffects().at("caeraguaSound").setChunkVolume(5);
			sdlutils().soundEffects().at("caeraguaSound").play(); //-----------------------------------------------------------		
		}
		else //Se mueve
		{
			//Personaje que queremos mover
			auto& pos = mapa->getCharacter(shader[i])->getComponent<Transform>()->getPos();
			auto* entit = mapa->getCharacter(shader[i]);

			mapa->removeCharacter(mapa->SDLPointToMapCoords(pos));
			pos.setX((newPos.getX() * cellWidth) + OFFSET_X);
			pos.setY((newPos.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP);
			mapa->setCharacter(mapa->SDLPointToMapCoords(pos), entit);

			sdlutils().soundEffects().at("loboSound").setChunkVolume(5);
			sdlutils().soundEffects().at("loboSound").play(); //-----------------------------------------------------------					
			//Pintar suelo
			if (mapa->getColor(mapa->SDLPointToMapCoords(pos)) != Rojo && entit->hasGroup<Equipo_Rojo>())
				mapa->setColor(mapa->SDLPointToMapCoords(pos), Rojo);
			else if (mapa->getColor(mapa->SDLPointToMapCoords(pos)) != Amarillo && entit->hasGroup<Equipo_Azul>())
				mapa->setColor(mapa->SDLPointToMapCoords(pos), Amarillo);
		}
	}
}