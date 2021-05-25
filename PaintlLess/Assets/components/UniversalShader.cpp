#include "UniversalShader.h"

void UniversalShader::update()
{
	if (lerpTime < 1) lerpTime += 0.25;
}

void UniversalShader::render()
{
	if (arrayPointer == nullptr || tex == nullptr) return;
	SDL_Rect dest;
	int cellWidth = mapa->getCellWidth();
	int cellHeight = mapa->getCellHeight();
	if (arrayPointer->size() > 0) {
		int aux = casillasRendered;
		for (Vector2D casilla : *arrayPointer) {
			float lerp = 0;
			if (aux > 0 && delayedCellsRender) lerp = 1;
			else if (aux == 0 || !delayedCellsRender) lerp = lerpTime;

			dest.w = cellWidth * lerp;
			dest.h = cellHeight * lerp;
			dest.x = (casilla.getX() * cellWidth + OFFSET_X) + cellWidth / 2 - dest.w / 2;
			dest.y = ((casilla.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP) + cellHeight / 2 - dest.h / 2;

			tex->render(dest);
			if (aux <= 0 && lerpTime >= 1)
			{
				if (!delayedCellsRender) continue;
				lerpTime = 0;
				casillasRendered++;
				break;
			}
			else aux--;
		}
	}
}

void UniversalShader::setCells(std::vector<Vector2D>* arrayPointer)
{
	this->arrayPointer = arrayPointer;
}

void UniversalShader::setTexture(Texture* tex)
{
	this->tex = tex;
}

void UniversalShader::resetLerp()
{
	lerpTime = 0;
}

void UniversalShader::resetCasillasRendered()
{
	casillasRendered = 0;
}

void UniversalShader::resetAnim()
{
	resetLerp();
	resetCasillasRendered();
}

void UniversalShader::checkCasillasPosiblesMov(const Vector2D& cSelected, uint casillasAMover, GameMap* mapa, std::vector<Vector2D>* casillasAPintar)
{
	Vector2D casillaAMirar;
	//Si se encuentra un obstaculo, el booleano correspondiente se pone a false
	//y no se comprueba mas por ese camino
	bool iz, der, up, down = iz = der = up = true;
	for (int i = 1; i <= casillasAMover; i++)
	{
		casillaAMirar = new Vector2D(cSelected.getX() + i, cSelected.getY());
		if (mapa->movimientoPosible(casillaAMirar) && der)
			casillasAPintar->push_back(casillaAMirar);
		else der = false;

		casillaAMirar = new Vector2D(cSelected.getX() - i, cSelected.getY());
		if (mapa->movimientoPosible(casillaAMirar) && iz)
			casillasAPintar->push_back(casillaAMirar);
		else iz = false;

		casillaAMirar = new Vector2D(cSelected.getX(), cSelected.getY() + i);
		if (mapa->movimientoPosible(casillaAMirar) && up)
			casillasAPintar->push_back(casillaAMirar);
		else up = false;

		casillaAMirar = new Vector2D(cSelected.getX(), cSelected.getY() - i);
		if (mapa->movimientoPosible(casillaAMirar) && down)
			casillasAPintar->push_back(casillaAMirar);
		else down = false;
	}
}

void UniversalShader::attackShader(const Vector2D& pos, GameMap* mapa, std::vector<Vector2D>* casillasAtaque, int range)
{
	Vector2D mapPos = mapa->SDLPointToMapCoords(pos);

	int i = 1; bool canAt = true;

	while (i <= range && canAt) {
		Vector2D posUp = Vector2D(0, i) + mapPos;
		if (mapa->getTipoCasilla(mapPos) == TipoCasilla::Base)
		{
			i++;
			continue;
		}
		if (mapa->casillaValida(posUp)) {
			if (mapa->ataquePosible(posUp))
				casillasAtaque->push_back(posUp);
			else if (mapa->getObstaculo(posUp) != nullptr) canAt = false;
		}
		i++;
	}
	i = 1; canAt = true;

	while (i <= range && canAt) {
		Vector2D posRight = Vector2D(i, 0) + mapPos;
		if (mapa->getTipoCasilla(mapPos) == TipoCasilla::Base)
		{
			i++;
			continue;
		}
		if (mapa->casillaValida(posRight)) {
			if (mapa->ataquePosible(posRight))
				casillasAtaque->push_back(posRight);
			else if (mapa->getObstaculo(posRight) != nullptr) canAt = false;
		}
		i++;
	}
	i = 1; canAt = true;

	while (i <= range && canAt) {
		Vector2D posLeft = Vector2D(-i, 0) + mapPos;
		if (mapa->getTipoCasilla(mapPos) == TipoCasilla::Base)
		{
			i++;
			continue;
		}
		if (mapa->casillaValida(posLeft)) {
			if (mapa->ataquePosible(posLeft))
				casillasAtaque->push_back(posLeft);
			else if (mapa->getObstaculo(posLeft) != nullptr) canAt = false;
		}
		i++;
	}
	i = 1; canAt = true;

	while (i <= range && canAt) {
		Vector2D posDown = Vector2D(0, -i) + mapPos;
		if (mapa->getTipoCasilla(mapPos) == TipoCasilla::Base)
		{
			i++;
			continue;
		}
		if (mapa->casillaValida(posDown)) {
			if (mapa->ataquePosible(posDown))
				casillasAtaque->push_back(posDown);
			else if (mapa->getObstaculo(posDown) != nullptr) canAt = false;
		}
		i++;
	}
}
