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

			if (aux > 0) lerp = 1;
			else if (aux == 0) lerp = lerpTime;

			dest.w = cellWidth * lerp;
			dest.h = cellHeight * lerp;
			dest.x = (casilla.getX() * cellWidth + OFFSET_X) + cellWidth / 2 - dest.w / 2;
			dest.y = ((casilla.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP) + cellHeight / 2 - dest.h / 2;

			tex->render(dest);
			if (aux <= 0 && lerpTime >= 1)
			{
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
