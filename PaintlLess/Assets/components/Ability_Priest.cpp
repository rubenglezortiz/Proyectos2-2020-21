#include "Ability_Priest.h"

void Ability_Priest::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	mapa_ = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	assert(mapa_ != nullptr);
	tex_ = &sdlutils().images().at("selectorH");
	cellWidth = mapa_->getCellWidth();
	cellHeight = mapa_->getCellHeight();
}

void Ability_Priest::heal() {
	for (int i = 0; i < casillasHeal.size(); i++) {
		if (mapa_->getCharacter(casillasHeal[i]) != nullptr) {
			if ((mapa_->getCharacter(casillasHeal[i])->hasGroup<Equipo_Azul>() && entity_->hasGroup<Equipo_Azul>()) || (mapa_->getCharacter(casillasHeal[i])->hasGroup<Equipo_Rojo>() && entity_->hasGroup<Equipo_Rojo>()))
			mapa_->getCharacter(casillasHeal[i])->getComponent<Health>()->healMonaguillo(1);
		}
	}
}

void Ability_Priest::healingShader() {
	posPriest = entity_->getComponent<Transform>()->getPos();
	posPriest = mapa_->SDLPointToMapCoords(posPriest);

	//Casillas 3x3
	Vector2D posUp = Vector2D(0, -1) + posPriest;
	if (mapa_->getTipoCasilla(posUp) != NoPintable) casillasHeal.push_back(posUp);
	Vector2D posUpLeft = Vector2D(-1, -1) + posPriest;
	if (mapa_->getTipoCasilla(posUpLeft) != NoPintable) casillasHeal.push_back(posUpLeft);
	Vector2D posUpRight = Vector2D(1, -1) + posPriest;
	if (mapa_->getTipoCasilla(posUpRight) != NoPintable) casillasHeal.push_back(posUpRight);
	Vector2D posRight = Vector2D(1, 0) + posPriest;
	if (mapa_->getTipoCasilla(posRight) != NoPintable) casillasHeal.push_back(posRight);
	Vector2D posLeft = Vector2D(-1, 0) + posPriest;
	if (mapa_->getTipoCasilla(posLeft) != NoPintable) casillasHeal.push_back(posLeft);
	Vector2D posDown = Vector2D(0, 1) + posPriest;
	if (mapa_->getTipoCasilla(posDown) != NoPintable) casillasHeal.push_back(posDown);
	Vector2D posDownLeft = Vector2D(-1, 1) + posPriest;
	if (mapa_->getTipoCasilla(posDownLeft) != NoPintable) casillasHeal.push_back(posDownLeft);
	Vector2D posDownRight = Vector2D(1, 1) + posPriest;
	if (mapa_->getTipoCasilla(posDownRight) != NoPintable) casillasHeal.push_back(posDownRight);

}
void Ability_Priest::update() {
	auto pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			heal();
			freeAbilityShader();
			selected = false;
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
			selected = true;
			healingShader();
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeAbilityShader();
	}
}

void Ability_Priest::render() {
	SDL_Rect dest;
	for (Vector2D casilla : casillasHeal) {
		dest.x = casilla.getX() * mapa_->getCellWidth() /*+ offset*/;
		dest.y = casilla.getY() * mapa_->getCellHeight()/*+ offset*/;
		dest.h = mapa_->getCellHeight();
		dest.w = mapa_->getCellWidth();
		tex_->render(dest);
	}
}

void Ability_Priest::freeAbilityShader() {
	casillasHeal.clear();
}