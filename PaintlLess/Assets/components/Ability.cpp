#include "./Ability.h"
#include "../game/PlayState.h"

void Ability::init() {
	map = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	assert(map != nullptr);
	characterTr = entity_->getComponent<Transform>();
	assert(characterTr != nullptr);
	cellWidth = map->getCellWidth();
	cellHeight = map->getCellHeight();
	string s;
	switch (sel)
	{
	case selector:
		s = "selector";
		break;
	case selectorA:
		s = "selectorA";
		break;
	case selectorH:
		s = "selectorH";
		break;
	default:
		break;
	}
	tex = &sdlutils().images().at(s);
}

void Ability::AbilityShader(ShaderForm sf, ShaderType st, int d) {
	Vector2D posCh = entity_->getComponent<Transform>()->getPos();
	posCh = entity_->getComponent<Transform>()->getPos();
	posCh = map->SDLPointToMapCoords(posCh);
	if (sf == Cross) {
		Vector2D posUp = Vector2D(0, d) + posCh;
		Vector2D posRight = Vector2D(d, 0) + posCh;
		Vector2D posLeft = Vector2D(-d, 0) + posCh;
		Vector2D posDown = Vector2D(0, -d) + posCh;

		if (st == AttackSh) {
			if (map->ataquePosible(posUp)) abilityCells.push_back(posUp);
			if (map->ataquePosible(posRight)) abilityCells.push_back(posRight);
			if (map->ataquePosible(posLeft)) abilityCells.push_back(posLeft);
			if (map->ataquePosible(posDown)) abilityCells.push_back(posDown);
		}
		else if (st == KirinSh) {
			cout << "Mi Posicion: " << map->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos()) << "Pos que miro: " << posUp;
			if (map->movimientoPosible(posUp) && map->getCharacter(posUp + Vector2D(0, -1)) != nullptr)abilityCells.push_back(posUp);
			if (map->movimientoPosible(posRight) && map->getCharacter(posRight + Vector2D(-1, 0)) != nullptr) abilityCells.push_back(posRight);
			if (map->movimientoPosible(posLeft) && map->getCharacter(posLeft + Vector2D(1, 0)) != nullptr) abilityCells.push_back(posLeft);
			if (map->movimientoPosible(posDown) && map->getCharacter(posDown + Vector2D(0, 1)) != nullptr) abilityCells.push_back(posDown);
		}
		else if (st == DruidaSh) {
			if (map->movimientoPosibleEnredadera(posUp)) abilityCells.push_back(posUp);
			if (map->movimientoPosibleEnredadera(posRight)) abilityCells.push_back(posRight);
			if (map->movimientoPosibleEnredadera(posLeft)) abilityCells.push_back(posLeft);
			if (map->movimientoPosibleEnredadera(posDown)) abilityCells.push_back(posDown);
		}
		else {
			if (map->movimientoPosible(posUp)) abilityCells.push_back(posUp);
			if (map->movimientoPosible(posRight)) abilityCells.push_back(posRight);
			if (map->movimientoPosible(posLeft)) abilityCells.push_back(posLeft);
			if (map->movimientoPosible(posDown)) abilityCells.push_back(posDown);
		}
	}
	else if (sf == TxT) {
		Vector2D posUp = Vector2D(0, -1) + posCh;
		if (map->getTipoCasilla(posUp) != NoPintable) abilityCells.push_back(posUp);
		Vector2D posUpLeft = Vector2D(-1, -1) + posCh;
		if (map->getTipoCasilla(posUpLeft) != NoPintable) abilityCells.push_back(posUpLeft);
		Vector2D posUpRight = Vector2D(1, -1) + posCh;
		if (map->getTipoCasilla(posUpRight) != NoPintable) abilityCells.push_back(posUpRight);
		Vector2D posRight = Vector2D(1, 0) + posCh;
		if (map->getTipoCasilla(posRight) != NoPintable) abilityCells.push_back(posRight);
		Vector2D posLeft = Vector2D(-1, 0) + posCh;
		if (map->getTipoCasilla(posLeft) != NoPintable) abilityCells.push_back(posLeft);
		Vector2D posDown = Vector2D(0, 1) + posCh;
		if (map->getTipoCasilla(posDown) != NoPintable) abilityCells.push_back(posDown);
		Vector2D posDownLeft = Vector2D(-1, 1) + posCh;
		if (map->getTipoCasilla(posDownLeft) != NoPintable) abilityCells.push_back(posDownLeft);
		Vector2D posDownRight = Vector2D(1, 1) + posCh;
		if (map->getTipoCasilla(posDownRight) != NoPintable) abilityCells.push_back(posDownRight);
	}
	else {
		bool findObj = false;

		Vector2D atDir;
		if (map->getPlayState()->getTurno() == Primero) atDir = Vector2D(-1, 0);
		else atDir = Vector2D(1, 0);

		posCh = map->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos()) + atDir;

		while (!findObj && map->casillaValida(posCh)) {
			if (map->ataquePosible(posCh))
				findObj = true;
			abilityCells.push_back(posCh);
			posCh = posCh + atDir;
		}
		if (!findObj)freeAbilityShader();

	}
}

void Ability::freeAbilityShader() { abilityCells.clear(); }

bool Ability::abilityCheck(const Vector2D& pos) {
	bool check = false;
	int cont = 0;
	while (!check && cont < abilityCells.size()) {
		if (pos == abilityCells[cont])check = true;
		cont++;
	}
	return check;
}


void Ability::render() {
	SDL_Rect dest;
	if (abilityCells.size() > 0) {
		for (Vector2D casilla : abilityCells) {
			dest.x = casilla.getX() * cellWidth /*+ offset*/;
			dest.y = casilla.getY() * cellHeight + OFFSET_Y;
			dest.h = cellHeight;
			dest.w = cellWidth;
			tex->render(dest);
		}
	}
}

void Ability::update() {
	if (map->getPlayState()->getTurno() == Primero && entity_->hasGroup<Equipo_Rojo>())
		return;
	if (map->getPlayState()->getTurno() == Segundo && entity_->hasGroup<Equipo_Azul>())
		return;

	auto pos = entity_->getComponent<Transform>()->getPos();
	if (ih().getMouseButtonState(ih().RIGHT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;

		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = map->SDLPointToMapCoords(Vector2D(mX, mY));

			if (abilityCheck(posMovimiento)) {
				ability_usable = false;
				pos.setX(posMovimiento.getX() * cellWidth);
				pos.setY(posMovimiento.getY() * cellHeight);
				AbilityExecute(posMovimiento.getX(), posMovimiento.getY());
			}
			selected = false;
			freeAbilityShader();

		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight && ability_usable) {
			selected = true;
			AbilityShader(form, type, shaderDistance);
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		selected = false;
		freeAbilityShader();
	}
}

void Ability::finTurno()
{
	ability_usable = true;
}
