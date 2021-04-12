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
};