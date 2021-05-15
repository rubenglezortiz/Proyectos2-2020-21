#include "./MovementShader.h"
#include "../game/OffsetInfo.h"

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

//m�todo recursivo que se llama en movimiento cuando se selecciona una casilla para comprobar a que casillas se puede mover
void MovementShader::casillasPosiblesRecu(const Vector2D& cSelected, vector<vector<CasillaMov>>& casillasChecked, uint casillasAMover) {
		//matriz igual que el tablero inicializada a false

		//Movimiento en cruz temporal hito
		Vector2D casillaAMirar;
		lerpTime = 0;
		numCasillasPintadas = 0;
		for (int i = 1; i <= casillasAMover; i++)
		{
			casillaAMirar = new Vector2D(cSelected.getX() + i, cSelected.getY());
			if (mapa->movimientoPosible(casillaAMirar))
			{
				casillasAPintar.push_back(casillaAMirar);
				casillasChecked[casillaAMirar.getX()][casillaAMirar.getY()].movPosible = true;
			}

			casillaAMirar = new Vector2D(cSelected.getX() - i, cSelected.getY());
			if (mapa->movimientoPosible(casillaAMirar))
			{
				casillasAPintar.push_back(casillaAMirar);
				casillasChecked[casillaAMirar.getX()][casillaAMirar.getY()].movPosible = true;
			}

			casillaAMirar = new Vector2D(cSelected.getX(), cSelected.getY() + i);
			if (mapa->movimientoPosible(casillaAMirar))
			{
				casillasAPintar.push_back(casillaAMirar);
				casillasChecked[casillaAMirar.getX()][casillaAMirar.getY()].movPosible = true;
			}

			casillaAMirar = new Vector2D(cSelected.getX(), cSelected.getY() - i);
			if (mapa->movimientoPosible(casillaAMirar))
			{
				casillasAPintar.push_back(casillaAMirar);
				casillasChecked[casillaAMirar.getX()][casillaAMirar.getY()].movPosible = true;
			}

		}

		//casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX(), cSelected.getY() - 1), casillasChecked, false);
		//casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX() + 1, cSelected.getY()), casillasChecked, false);
		//casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX(), cSelected.getY() + 1), casillasChecked, false);
		//casillasPosiblesRecuAux(casillasAMover - 1, cSelected, Vector2D(cSelected.getX() - 1, cSelected.getY()), casillasChecked, false);

		//para no volver a acceder a la inicial
		casillasChecked[cSelected.getX()][cSelected.getY()].checked = true;
	
		casillasBaseRecorridas.clear();


	//if (!(cSelected.getX() == 0 && cActual.getX() != 0))

}


void MovementShader::casillasPosiblesRecuAux(int casillasAMover, const Vector2D& cSelected, const Vector2D& cActual, vector<vector<CasillaMov>>& casillasChecked, bool base) {

	//si se ha quedado sin movimiento se devuelve la llamada
	if (casillasAMover == 0) return;

	//si la casilla est� fuera del mapa no hago nada
	if (cActual.getX() < 0 || cActual.getX() >= mapa->getColumns() ||
		cActual.getY() < 0 || cActual.getY() >= mapa->getRows()) return;

	bool estaEnBase = false;
	int suma = -1;
	if (cSelected.getX() == 0) {

		if (base && cActual.getX() == 0) {
			for (auto casillaBase : casillasBaseRecorridas) {
				if (cActual.getX() == casillaBase.first.getX() && cActual.getY() == casillaBase.first.getY()) {
					if (casillasAMover > casillaBase.second) {
						casillaBase.second = casillasAMover;
					}
					else {
						return;
					}
				}
			}
			suma = 0;
			casillasBaseRecorridas.push_back(pair<Vector2D, int>(cActual, casillasAMover));
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

void MovementShader::update() {
	if (lerpTime < 1) lerpTime += 0.2;
}

void MovementShader::render() {
	SDL_Rect dest;
	for (Vector2D casilla : casillasAPintar) {
		dest.x = casilla.getX() * cellWidth + OFFSET_X;
		dest.y = (casilla.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP;
		dest.h = cellHeight * lerpTime;
		dest.w = cellWidth * lerpTime;

		tex_->render(dest);
	}
}

void MovementShader::freeCasillasAPintar() {
	casillasAPintar.clear();
}