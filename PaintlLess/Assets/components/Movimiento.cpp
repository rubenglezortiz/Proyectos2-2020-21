#include "./Movimiento.h"
#include "../game/PlayState.h"
#include "../game/OffsetInfo.h"


void Movimiento::init() {
	tr_ = entity_->getComponent<Transform>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	movShader = entity_->getMngr()->getHandler<BoardManager>()->getComponent<MovementShader>();
	//mapa->setCharacter(mapa->SDLPointToMapCoords(tr_->getPos()), entity_);
	initializeCasillasChecked();
	assert(tr_ != nullptr);
}

void Movimiento::update() {

	if (entity_->hasGroup<Equipo_Azul>() && playState->getTurno() == Primero || entity_->hasGroup<Equipo_Rojo>() && playState->getTurno() == Segundo) {

		if (playState->getAcciones() > 0) {


			auto& pos = tr_->getPos();
			//poner el puntero de entidad de la casilla del mapa a NULL

			if (ih().getMouseButtonState(ih().LEFT)) {
				int mX = ih().getMousePos().first;
				int mY = ih().getMousePos().second;
				if (selected) {
					//esto se debe hacer en movementshader
					Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));
					if (casillasChecked[posMovimiento.getX()][posMovimiento.getY()].movPosible) {
						mapa->removeCharacter(mapa->SDLPointToMapCoords(pos));
						pos.setX(posMovimiento.getX() * cellWidth);
						pos.setY((posMovimiento.getY() * cellHeight)+ OFFSET_Y);
						mapa->setCharacter(mapa->SDLPointToMapCoords(pos), entity_);
						playState->aumentarAcciones();
						cout << pos;
					}
					selected = false;

					if(entity_->hasGroup<Equipo_Azul>())
						mapa->setColor(mapa->SDLPointToMapCoords(pos), Amarillo);
					else
						mapa->setColor(mapa->SDLPointToMapCoords(pos), Rojo); 

					//estos métodos son para cuando se deselcciona yuna casilla para restablecer los valores de los vectores...
					movShader->freeCasillasAPintar();
					resetCasillasChecked();
				}
				else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
					selected = true;
					movShader->casillasPosiblesRecu(mapa->SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY())), casillasChecked);
					sdlutils().soundEffects().at("click").play(); //-----------------------------------------------------------
				}
			}
			if (ih().getMouseButtonState(ih().RIGHT)) {
				selected = false;
				resetCasillasChecked();
				movShader->freeCasillasAPintar();
			}
		}
		/*else {
			cout << "sin acciones";
		}*/
		
	}
	
}

void Movimiento::finTurno()
{
	movShader->freeCasillasAPintar();
}

void Movimiento::initializeCasillasChecked() { //AAAAAAAAAAAAAA
	//ese método es porque no sabemos inicializar el vector y daba errores UwU
	vector<vector<MovementShader::CasillaMov>> casillasCheckedAux(mapa->getColumns(), vector<MovementShader::CasillaMov>(mapa->getRows(), { false, false }));;
	casillasChecked = casillasCheckedAux;
}

void Movimiento::resetCasillasChecked() {
	for (int x = 0; x < mapa->getColumns(); x++) {
		for (int y = 0; y < mapa->getRows(); y++) {
			casillasChecked[x][y].checked = false;
			casillasChecked[x][y].movPosible = false;
		}
	}
}