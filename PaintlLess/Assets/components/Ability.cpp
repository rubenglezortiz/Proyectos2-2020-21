#include "./Ability.h"
#include "../game/PlayState.h"
#include "../game/GameStateMachine.h"
#include "../game//AbilityStruct.h"

Ability::Ability(AbilityStruct data) : characterTr(nullptr), tex(nullptr), map(nullptr), abilityData(data),
sel(abilityData.selector), selected(false), cellWidth(0), cellHeight(0), form(abilityData.shaderForm), type(abilityData.shaderType), shaderDistance(1) { }

void Ability::init() {
	abilityData.setSelf(this);
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
		s = "selectorAb";
		break;
	case selectorA:
		s = "selectorA";
		break;
	case selectorH:
		s = "selectorH";
		break;
	default:
		s = "selectorAb";
		break;
	}
	tex = &sdlutils().images().at(s);
	auto mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	playState = mapa->getPlayState();
}

void Ability::AbilityExecute(int x, int y)
{
	abilityData.AbilityExecute(x, y);
}

void Ability::AbilityShader(ShaderForm sf, ShaderType st, int d) {
	Vector2D posCh = entity_->getComponent<Transform>()->getPos();
	posCh = entity_->getComponent<Transform>()->getPos();
	posCh = map->SDLPointToMapCoords(posCh);
	lerpTime = 0;
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
			if (map->movimientoPosible(posUp) && (map->getCharacter(posUp + Vector2D(0, -1)) != nullptr ||
				map->getCreeper(posUp + Vector2D(0, -1))))abilityCells.push_back(posUp);


			if (map->movimientoPosible(posRight) && (map->getCharacter(posRight + Vector2D(-1, 0)) != nullptr ||
				map->getCreeper(posRight + Vector2D(-1, 0)))) abilityCells.push_back(posRight);


			if (map->movimientoPosible(posLeft) && (map->getCharacter(posLeft + Vector2D(1, 0)) != nullptr ||
				map->getCreeper(posLeft + Vector2D(1, 0)))) abilityCells.push_back(posLeft);
			if (map->movimientoPosible(posDown) && (map->getCharacter(posDown + Vector2D(0, 1)) != nullptr ||
				map->getCreeper(posDown + Vector2D(0, 1)))) abilityCells.push_back(posDown);
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
		if (map->casillaValida(posUp) && map->getTipoCasilla(posUp) != NoPintable) abilityCells.push_back(posUp);
		Vector2D posUpLeft = Vector2D(-1, -1) + posCh;
		if (map->casillaValida(posUpLeft) && map->getTipoCasilla(posUpLeft) != NoPintable) abilityCells.push_back(posUpLeft);
		Vector2D posUpRight = Vector2D(1, -1) + posCh;
		if (map->casillaValida(posUpRight) && map->getTipoCasilla(posUpRight) != NoPintable) abilityCells.push_back(posUpRight);
		Vector2D posRight = Vector2D(1, 0) + posCh;
		if (map->casillaValida(posRight) && map->getTipoCasilla(posRight) != NoPintable) abilityCells.push_back(posRight);
		Vector2D posLeft = Vector2D(-1, 0) + posCh;
		if (map->casillaValida(posLeft) && map->getTipoCasilla(posLeft) != NoPintable) abilityCells.push_back(posLeft);
		Vector2D posDown = Vector2D(0, 1) + posCh;
		if (map->casillaValida(posDown) && map->getTipoCasilla(posDown) != NoPintable) abilityCells.push_back(posDown);
		Vector2D posDownLeft = Vector2D(-1, 1) + posCh;
		if (map->casillaValida(posDownLeft) && map->getTipoCasilla(posDownLeft) != NoPintable) abilityCells.push_back(posDownLeft);
		Vector2D posDownRight = Vector2D(1, 1) + posCh;
		if (map->casillaValida(posDownRight) && map->getTipoCasilla(posDownRight) != NoPintable) abilityCells.push_back(posDownRight);
	}
	else if (sf == ShaderWolf) {
		std::vector<Vector2D> casillas;
		Vector2D detras;
		if (entity_->hasGroup<Equipo_Rojo>()) {
			casillas = { {1, 0}, {2, 0}, { 1, 1}, {2, 1}, {1, -1}, {2, -1} }; //Izquierda ==> Derecha
			detras = Vector2D(1, 0);
		}
		else {
			casillas = { {-1, 0}, {-2, 0}, {-1, 1}, {-2, 1}, {-1, -1}, {-2, -1} }; //Derecha ==> Izquierda
			detras = Vector2D(-1, 0);
		}

		Vector2D posWolf = map->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos());

		for (int i = 0; i < casillas.size(); i++) { // 12, 2 por cada lao
			if (map->casillaValida(casillas[i] + posWolf)) {
				//Hay personaje en el 1
				if (map->getCharacter(casillas[i] + posWolf) != nullptr) {
					if (map->casillaValida(casillas[i] + posWolf + detras)) abilityCells.push_back(casillas[i] + posWolf);
				}
				//Hay personaje en el 2
				else if (map->getCharacter(casillas[i + 1] + posWolf) != nullptr)
				{
					if (map->casillaValida(casillas[i] + posWolf + detras * 2)) abilityCells.push_back(casillas[i + 1] + posWolf);
				}
			}
			i++;
		}
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
			if (map->getCharacter(posCh) != nullptr) {
				if (map->ataquePosible(posCh))
					abilityCells.push_back(posCh);
			}
			else
				abilityCells.push_back(posCh);
			posCh = posCh + atDir;
		}
		if (!findObj)freeAbilityShader();
	}
	casillasRendered = 0;
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
		int aux = casillasRendered;
		for (Vector2D casilla : abilityCells) {
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

void Ability::update() {
	if (map->getPlayState()->getTurno() == Primero && entity_->hasGroup<Equipo_Rojo>())
		return;
	if (map->getPlayState()->getTurno() == Segundo && entity_->hasGroup<Equipo_Azul>())
		return;

	if (lerpTime < 1) lerpTime += 0.25;

	auto pos = entity_->getComponent<Transform>()->getPos();

	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (ih().getMouseButtonState(ih().RIGHT)) {
		if (!selected && entity_->hasComponent<Movimiento>() && playState->getAcciones() > 0 && entity_->getComponent<Movimiento>()->getStun() == 0)
		{
			if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight && ability_usable) {
				selected = true;
				AbilityShader(form, type, shaderDistance);
			}
		}
		else
		{
			selected = false;
			freeAbilityShader();
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = map->SDLPointToMapCoords(Vector2D(mX, mY));

			if (abilityCheck(posMovimiento)) {
				ability_usable = false;
				pos.setX(posMovimiento.getX() * cellWidth);
				pos.setY(posMovimiento.getY() * cellHeight);
				int x = posMovimiento.getX();
				int y = posMovimiento.getY();
				auto character = this->map->getCharacter(Vector2D(x, y));
				if (character != nullptr)
				{
					auto mov = character->getComponent<Movimiento>();
					if (mov != nullptr) mov->focus();
				}
				AbilityExecute(x, y);
				Vector2D charPos = characterTr->getPos();
				if(playState->getGSM()->isOnline())playState->getGSM()->getNetworkManager()->sendExecuteAbility(charPos.getX(), charPos.getY(), 
					std::forward<int>(x), std::forward<int>(y));
				playState->aumentarAcciones();
			}
			selected = false;
			freeAbilityShader();
		}
	}
}


void Ability::finTurno()
{
	ability_usable = true;
	freeAbilityShader();
	abilityData.finTurno();
}
