#include "./MovementShader.h"

MovementShader::MovementShader(Texture* t) {
	cont = 0; 
	dest = SDL_Rect();
	mapa = nullptr;
	resultado = 0;
	cellWidth = 0; cellHeight = 0;
	position = Vector2D();
	tex_ = t;
	src_ = SDL_Rect();
}

void MovementShader::init() {
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
}

void MovementShader::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;

	if (sdlutils().currRealTime() > cont + 10) {
		resultado = mX / mapa->getCellWidth();
		dest.x = resultado * mapa->getCellWidth();
		resultado = mY / mapa->getCellHeight();
		dest.y = resultado * mapa->getCellHeight();
		cont = sdlutils().currRealTime();
	}
}

//método recursivo que se llama en movimiento cuando se selecciona una casilla para comprobar a que casillas se puede mover
void MovementShader::casillasPosiblesRecu(const Vector2D& cSelected, vector<vector<CasillaMov>>& casillasChecked) {

	uint casillasAMover = UnitInfo::Movimiento[Alquimista];
	//matriz igual que el tablero inicializada a false

	casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX(), cSelected.getY() - 1), casillasChecked, false);
	casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX() + 1, cSelected.getY()), casillasChecked, false);
	casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX(), cSelected.getY() + 1), casillasChecked, false);
	casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX() - 1, cSelected.getY()), casillasChecked, false);

	//para no volver a acceder a la inicial
	casillasChecked[cSelected.getX()][cSelected.getY()].checked = true;

	size = 0;
	numCasillas = 0;
	//if (!(cSelected.getX() == 0 && cActual.getX() != 0))

}


void MovementShader::casillasPosiblesRecuAux(int casillasAMover, const Vector2D& cSelected, const Vector2D& cActual, vector<vector<CasillaMov>>& casillasChecked, bool base) {

	//si se ha quedado sin movimiento se devuelve la llamada
	if (casillasAMover == 0) return;

	//si la casilla está fuera del mapa no hago nada
	if (cActual.getX() < 0 || cActual.getX() >= mapa->getColumns() ||
		cActual.getY() < 0 || cActual.getY() >= mapa->getRows()) return;

	bool estaEnBase = false;
	int suma = -1;
	if (cSelected.getX() == 0) {

		if (base && cActual.getX() == 0) {
			suma = 0;
		}
		estaEnBase = true;
	}


	int a = cActual.getX();
	int b = cActual.getY();
	//si la casilla a la que accedo no ha sido visitada
	if (/*!casillasChecked[cActual.getX()][cActual.getY()].checked &&*/
		mapa->movimientoPosible(Vector2D(cActual.getX(), cActual.getY()))) {

		if (!(cSelected.getX() == 0 && cActual.getX() != 0)) casillasChecked[cActual.getX()][cActual.getY()].checked = true;

		if (!casillasChecked[cActual.getX()][cActual.getY()].movPosible) {
			casillasAPintar.push_back(Vector2D(cActual.getX(), cActual.getY()));
			casillasChecked[cActual.getX()][cActual.getY()].movPosible = true;
		}
		

		casillasPosiblesRecuAux(casillasAMover + suma, cSelected, Vector2D(cActual.getX(), cActual.getY() - 1), casillasChecked, estaEnBase);
		casillasPosiblesRecuAux(casillasAMover + suma, cSelected, Vector2D(cActual.getX() + 1, cActual.getY()), casillasChecked, estaEnBase);
		casillasPosiblesRecuAux(casillasAMover + suma, cSelected, Vector2D(cActual.getX(), cActual.getY() + 1), casillasChecked, estaEnBase);
		casillasPosiblesRecuAux(casillasAMover + suma, cSelected, Vector2D(cActual.getX() - 1, cActual.getY()), casillasChecked, estaEnBase);
	}
}

void MovementShader::render() {
	SDL_Rect dest;

	if (size < 1) size += 0.1;
	int cas = 0;
	numCasillas++;

	for (Vector2D casilla : casillasAPintar) {
		if (cas == numCasillas) return;
		dest.x = casilla.getX() * cellWidth  /*+ offset*/;
		dest.y = casilla.getY() * cellHeight /*+ offset*/;
		dest.h = cellHeight * size;
		dest.w = cellWidth  * size;

		tex_->render(dest);
		cas++;
	}
}

void MovementShader::freeCasillasAPintar() {
	casillasAPintar.clear();
}