#pragma once
#include "GameState.h"
#include <vector>

using namespace std;

/*
* PlayState maneja la partida en curso.
*/

enum Equipo { Primero, Segundo };

class PlayState : public GameState
{

private:
	const int MAX_TURNOS = 10;
	const int MAX_ACCIONES = 3;
	int accionesPorTurno = MAX_ACCIONES, turnosActuales = 0;
	int mana;
	Equipo jugadorActual = Segundo;
public:
	// Constructora.
	PlayState(GameStateMachine* gsm, vector<bool> charss);
	// Destructora.
	virtual ~PlayState();


	// Métodos que crean a los personajes.
	void createAlquimista(Equipo c);
	void createArquitecta(Equipo c);
	void createCazador(Equipo c);
	void createBomba(Equipo c);
	void createDruida(Equipo c);
	void createEsqueleto(Equipo c);
	void createGolem(Equipo c);
	void createKirin(Equipo c);
	void createLobo(Equipo c);
	void createMonaguillo(Equipo c);
	void createTanque(Equipo c);
	void createPicara(Equipo c);
	void createVikingo(Equipo c);




	void pasaTurno();
	Equipo getTurno() const { return jugadorActual; }

	void aumentarAcciones() { accionesPorTurno--; };
	int getAcciones() const { return accionesPorTurno; }
	

	
};