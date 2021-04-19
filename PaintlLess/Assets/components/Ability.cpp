#include "./Ability.h"


void Ability::init() {
	map = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
}

void Ability::AbilityShader(ShaderType st, ShaderForm sf, int d) {
	Vector2D posCh = entity_->getComponent<Transform>()->getPos();
	if (sf == Cross) {
		posCh = entity_->getComponent<Transform>()->getPos();
		posCh = map->SDLPointToMapCoords(posCh);
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
		while (!findObj && map->casillaValida(posCh)) {
			if (map->ataquePosible(posCh))
				findObj = true;
			abilityCells.push_back(posCh);
			posCh = posCh + Vector2D(1, 0);
		}
		if (!findObj)freeAbilityShader();
	}
}

void Ability::freeAbilityShader() { abilityCells.clear(); }