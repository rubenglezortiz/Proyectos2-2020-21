#pragma once
#include "GameState.h"
#include <vector>

using namespace std;

/*
* PlayState maneja la partida en curso.
*/

enum Equipo { Primero, Segundo };
class GameMap;
class PlayState : public GameState
{

private:
	const int MAX_TURNOS = 10;
	const int MAX_ACCIONES = 3;
	const int MAX_MANA = 10;
	const int INCREMENTO_MANA = 3;
	int mana_1 = 10;
	int mana_2 = 10;
	int accionesPorTurno = MAX_ACCIONES, turnosActuales = 0;
	int mana;
	Equipo jugadorActual = Segundo;
	GameMap* mapa;
public:

	// Constructora.
	PlayState(GameStateMachine* gsm, vector<bool> charss);
	// Destructora.
	virtual ~PlayState();

	// Método que crea el mazo.
	void createMazo(int n, int i);

	void pasaTurno();
	Equipo getTurno() const { return jugadorActual; }

	PlayState* getPlayState() { return this; }
	Equipo getCurrentPlayer() { return jugadorActual; }

	void aumentarAcciones() { accionesPorTurno--; };
	int getAcciones() const { return accionesPorTurno; }	
	int& getMana1()  { return mana_1; } //Para interfaz
	int& getMana2()  { return mana_2; }

	bool restaMana(int m, int& mana);
	bool manaSuficiente(int m, int mana) const;
};