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

	if (casillasAMover != 0) {
		if ((entity_->hasGroup<Equipo_Azul>() && playState->getTurno() == Primero || entity_->hasGroup<Equipo_Rojo>() && playState->getTurno() == Segundo) && stun == 0) {

			if (playState->getAcciones() > 0) {


				auto& pos = tr_->getPos();
				Vector2D posIni = pos;
				//poner el puntero de entidad de la casilla del mapa a NULL

				if (ih().getMouseButtonState(ih().LEFT)) {
					int mX = ih().getMousePos().first;
					int mY = ih().getMousePos().second;

					if (selected) {
						//esto se debe hacer en movementshader
						Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));

						//si está dentro de los margenes del tablero
						if (posMovimiento.getX() >= 0 && posMovimiento.getY() >= 0 &&
							posMovimiento.getX() < mapa->getColumns() && posMovimiento.getY() < mapa->getRows()) {

							if (casillasChecked[posMovimiento.getX()][posMovimiento.getY()].movPosible) {
								mapa->removeCharacter(mapa->SDLPointToMapCoords(pos));
								pos.setX((posMovimiento.getX() * cellWidth) + OFFSET_X);
								pos.setY((posMovimiento.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP);
								mapa->setCharacter(mapa->SDLPointToMapCoords(pos), entity_);
								playState->aumentarAcciones();
								cout << pos;
							}
							selected = false;
							//sdlutils().soundEffects().at("moveSound").setChunkVolume(5);
							sdlutils().soundEffects().at("moveSound").play(); //-----------------------------------------------------------		

							if (entity_->hasGroup<Equipo_Azul>()) {

								colorea(posIni, pos, Amarillo);

							}
							else {


								colorea(posIni, pos, Rojo);
								//float  desplX, desplY;
								////solo se pueden mover en linea recta en un eje, no hay diagonal, por lo que el que de != 0 de estos es el eje en el que
								////Se mueve
								//Vector2D posCoor = mapa->SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY()));
								//Vector2D posIniCoor = mapa->SDLPointToMapCoords(Vector2D(posIni.getX(), posIni.getY()));

								//desplX = posCoor.getX() - posIniCoor.getX();
								//desplY = posCoor.getY() - posIniCoor.getY();

								//if (desplX != 0) {
								//	if (desplX > 0) {
								//		for (int a = posIniCoor.getX(); a <= posCoor.getX(); a++) {
								//			mapa->setColor((Vector2D(a, posCoor.getY())), Rojo);
								//		}
								//	}
								//	else {
								//		for (int a = posIniCoor.getX(); a >= posCoor.getX(); a--) {
								//			mapa->setColor((Vector2D(a, posCoor.getY())), Rojo);
								//		}
								//	}
								//}


								//if (desplY != 0) {
								//	if (desplY > 0) {
								//		for (int a = posIniCoor.getY(); a <= posCoor.getY(); a++) {
								//			mapa->setColor((Vector2D(posCoor.getX(), a)), Rojo);
								//		}
								//	}
								//	else {
								//		for (int a = posIniCoor.getY(); a >= posCoor.getY(); a-- ) {
								//			mapa->setColor((Vector2D(posCoor.getX(), a)), Rojo);
								//		}
								//	}
								//}
							}


							//estos métodos son para cuando se deselcciona yuna casilla para restablecer los valores de los vectores...
							movShader->freeCasillasAPintar();
							resetCasillasChecked();
						}

					}
					else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
						selected = true;
						movShader->casillasPosiblesRecu(mapa->SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY())), casillasChecked, casillasAMover);
						//sdlutils().soundEffects().at("click").setChunkVolume(5);
						sdlutils().soundEffects().at("click").play(); //-----------------------------------------------------------					
					}
				}
				if (ih().getMouseButtonState(ih().RIGHT) || focused) {
					selected = false;
					focused = false;
					resetCasillasChecked();
					movShader->freeCasillasAPintar();
				}
			}
			/*else {
				cout << "sin acciones";
			}*/

		}
	}	
}

void Movimiento::finTurno()
{
	movShader->freeCasillasAPintar();
	if (stun > 0)
	{
		stun--;
	}
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

void Movimiento::colorea(Vector2D posIni, Vector2D posFin, Color color)
{
	float  desplX, desplY;
	//solo se pueden mover en linea recta en un eje, no hay diagonal, por lo que el que de != 0 de estos es el eje en el que
	//Se mueve
	Vector2D posCoor = mapa->SDLPointToMapCoords(Vector2D(posFin.getX(), posFin.getY()));
	Vector2D posIniCoor = mapa->SDLPointToMapCoords(Vector2D(posIni.getX(), posIni.getY()));

	desplX = posCoor.getX() - posIniCoor.getX();
	desplY = posCoor.getY() - posIniCoor.getY();

	if (desplX != 0) {
		if (desplX > 0) {  //mirar el alquimista si pinta de mas
			for (int a = posIniCoor.getX(); a <= posCoor.getX(); a++) {
				mapa->setColor((Vector2D(a, posCoor.getY())), color);				
			}
		}
		else {
			for (int a = posIniCoor.getX(); a >= posCoor.getX(); a--) {
				mapa->setColor((Vector2D(a, posCoor.getY())), color);				
			}
		}
	}


	if (desplY != 0) {
		if (desplY > 0) {
			for (int a = posIniCoor.getY(); a <= posCoor.getY(); a++) {
				mapa->setColor((Vector2D(posCoor.getX(), a)), color);
			}
		}
		else {
			for (int a = posIniCoor.getY(); a >= posCoor.getY(); a--) {
				mapa->setColor((Vector2D(posCoor.getX(), a)), color);
			}
		}
	}
}
