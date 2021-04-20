#include "Ability_Kirin.h"

void Ability_Kirin::init()
{
	tr = entity_->getComponent<Transform>();
	assert(tr != nullptr);
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	assert(mapa != nullptr);

	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	tex = &sdlutils().images().at("selector");
}

void Ability_Kirin::update() {
	auto& pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));

			if (posibleMov(posMovimiento))
			{
				mapa->removeCharacter(mapa->SDLPointToMapCoords(pos));
				pos.setX(posMovimiento.getX() * cellWidth);
				pos.setY(posMovimiento.getY() * cellHeight);
				mapa->setCharacter(mapa->SDLPointToMapCoords(pos), entity_);
			}

			mapa->setColor(mapa->SDLPointToMapCoords(pos), Amarillo);

			selected = false;
			freeAbilityShader();
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			selected = true;
			AbilityShader();
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeAbilityShader();
	}
}

bool Ability_Kirin::posibleMov(Vector2D pos) {
	bool esPosible = false;
	int i = 0;
	while (!esPosible && i < casillas.size()) {
		if (pos == casillas[i])esPosible = true;
		i++;
	}
	return esPosible;
}

void Ability_Kirin::AbilityShader() {
	posKir = entity_->getComponent<Transform>()->getPos();

	posKir = mapa->SDLPointToMapCoords(posKir);

	//Casillas +
	Vector2D posUp = Vector2D(0, -1) + posKir; //Up

	if (mapa->casillaValida(posUp) && (mapa->getCharacter(posUp) != nullptr || mapa->getTipoCasilla(posUp) == NoPintable))
	{
		Vector2D posUp2 = Vector2D(0, -2) + posKir;
		if (mapa->movimientoPosible(posUp2))
			casillas.push_back(posUp2);
	}

	Vector2D posRight = Vector2D(1, 0) + posKir; //Right

	if (mapa->casillaValida(posRight) && (mapa->getCharacter(posRight) != nullptr || mapa->getTipoCasilla(posRight) == NoPintable))
	{
		Vector2D posRight2 = Vector2D(2, 0) + posKir;
		if (mapa->movimientoPosible(posRight2))
			casillas.push_back(posRight2);
	}

	Vector2D posLeft = Vector2D(-1, 0) + posKir; //Left

	if (mapa->casillaValida(posLeft) && (mapa->getCharacter(posLeft) != nullptr || mapa->getTipoCasilla(posLeft) == NoPintable))
	{
		Vector2D posLeft2 = Vector2D(-2, 0) + posKir;
		if (mapa->movimientoPosible(posLeft2))
			casillas.push_back(posLeft2);
	}

	Vector2D posDown = Vector2D(0, 1) + posKir; //Down

	if (mapa->casillaValida(posDown) && (mapa->getCharacter(posDown) != nullptr || mapa->getTipoCasilla(posDown) == NoPintable))
	{
		Vector2D posDown2 = Vector2D(0, 2) + posKir;
		if (mapa->movimientoPosible(posDown2))
			casillas.push_back(posDown2);
	}
}

void Ability_Kirin::render() {
	SDL_Rect dest;

	for (int i = 0; i < casillas.size(); ++i) {
		dest.x = casillas[i].getX() * cellWidth /*+ offset*/;
		dest.y = casillas[i].getY() * cellHeight + OFFSET_Y/*+ offset*/;
		dest.h = cellHeight;
		dest.w = cellWidth;
		tex->render(dest);
	}
}