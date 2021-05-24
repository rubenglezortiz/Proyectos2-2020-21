#include "./Movimiento.h"
#include "../game/PlayState.h"
#include "../game/OffsetInfo.h"
#include "../game/GameStateMachine.h"
#include "Ability.h"

void Movimiento::init() {
	tr_ = entity_->getComponent<Transform>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	movShader = entity_->getMngr()->getHandler<BoardManager>()->getComponent<MovementShader>();
	gsm = playState->getGSM();
	//mapa->setCharacter(mapa->SDLPointToMapCoords(tr_->getPos()), entity_);
	initializeCasillasChecked();
	assert(tr_ != nullptr);
}

void Movimiento::update() {
	if (casillasAMover == 0) return;
	if ((gsm->isOnline() &&
		((gsm->getNetworkManager()->isMaster() && entity_->hasGroup<Equipo_Rojo>() && playState->getTurno() == Segundo) ||
			(!gsm->getNetworkManager()->isMaster() && entity_->hasGroup<Equipo_Azul>() && playState->getTurno() == Primero))) ||

		(!gsm->isOnline() && (entity_->hasGroup<Equipo_Azul>() && playState->getTurno() == Primero || entity_->hasGroup<Equipo_Rojo>() && playState->getTurno() == Segundo) && stun == 0)) {
		if (playState->getAcciones() == 0)return;
		auto& pos = tr_->getPos();
		Vector2D posIni = pos;
		//poner el puntero de entidad de la casilla del mapa a NULL

		if (ih().getMouseButtonState(ih().LEFT)) {
			int mX = ih().getMousePos().first;
			int mY = ih().getMousePos().second;

			if (selected) {
				//esto se debe hacer en movementshader
				Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));

				if (casillasChecked[posMovimiento.getX()][posMovimiento.getY()].movPosible)
				{
					MoveCharacter(posIni, posMovimiento);
					if(gsm->isOnline())gsm->getNetworkManager()->sendMoveMessage(posIni.getX(), posIni.getY(), posMovimiento.getX(), posMovimiento.getY());
				}
				selected = false;
				movShader->freeCasillasAPintar();
				resetCasillasChecked();
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
}

void Movimiento::finTurno()
{
	movShader->freeCasillasAPintar();
	if (stun > 0)
	{
		stun--;
	}
}

void Movimiento::MoveCharacter(const Vector2D& posIni, const Vector2D& destino)
{
	auto& pos = tr_->getPos();
	sdlutils().soundEffects().at("moveSound").play();
	mapa->removeCharacter(mapa->SDLPointToMapCoords(pos));
	pos.setX((destino.getX() * cellWidth) + OFFSET_X);
	pos.setY((destino.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP);
	mapa->setCharacter(mapa->SDLPointToMapCoords(pos), entity_);
	playState->aumentarAcciones();
	cout << pos;

	if (entity_->hasGroup<Equipo_Azul>()) colorea(posIni, pos, Azul);
	else colorea(posIni, pos, Rojo);
}

void Movimiento::initializeCasillasChecked() { //AAAAAAAAAAAAAA
	//ese m�todo es porque no sabemos inicializar el vector y daba errores UwU
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
	bool haCambiado = false;;
	if (desplX != 0) {
		if (desplX > 0) {  //mirar el alquimista si pinta de mas
			for (int a = posIniCoor.getX(); a <= posCoor.getX(); a++) {
				haCambiado = mapa->setColor((Vector2D(a, posCoor.getY())), color);
			}
		}
		else {
			for (int a = posIniCoor.getX(); a >= posCoor.getX(); a--) {
				haCambiado = mapa->setColor((Vector2D(a, posCoor.getY())), color);
			}
		}
	}


	if (desplY != 0) {
		if (desplY > 0) {
			for (int a = posIniCoor.getY(); a <= posCoor.getY(); a++) {
				haCambiado = mapa->setColor((Vector2D(posCoor.getX(), a)), color);
			}
		}
		else {
			for (int a = posIniCoor.getY(); a >= posCoor.getY(); a--) {
				haCambiado = mapa->setColor((Vector2D(posCoor.getX(), a)), color);
			}
		}
	}

	if (haCambiado)
		entity_->getComponent<Ability>()->OnCross();

}
