#pragma once
#include "GameState.h"
#include <vector>
class EntityFactory;
class Network;

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
	const int MAX_ACCIONES = 4;
	const int MAX_MANA = 10;
	const int INCREMENTO_MANA = 3;
	int mana_1 = 10;
	int mana_2 = 10;
	int accionesPorTurno = MAX_ACCIONES, turnosActuales = 0;
	int mana;
	int pintado_1, pintado_2;
	Equipo jugadorActual = Segundo;
	vector<bool> ch1, ch2;
	GameMap* mapa_;
	Network* net;
public:

	// Constructora.
	PlayState(GameStateMachine* gsm, vector<bool> charss, vector<bool> charss2, int mapa, int tileset);
	// Destructora.
	virtual ~PlayState();

	// Método que crea el mazo.
	void createMazo(int n, int x, int equipo);
	void mazoEquipo();
	void moveMazo();
	void update() override;
	void moveChar(Vector2D charPosInMap, Vector2D dest);

	GameMap* getMapa() { return mapa_; }

	void pasaTurno();
	Equipo getTurno() const { return jugadorActual; }

	PlayState* getPlayState() { return this; }
	Equipo getCurrentPlayer() { return jugadorActual; }
	GameStateMachine* getGSM() { return gameStateMachine; }

	void aumentarAcciones() { accionesPorTurno--; };
	int getAcciones() const { return accionesPorTurno; }	
	int& getMana1()  { return mana_1; } //Para interfaz
	int& getMana2()  { return mana_2; }

	int getTurnosActuales()  { return turnosActuales; }

	bool restaMana(int m, int& mana);
	bool manaSuficiente(int m, int mana) const;

	int getPorcentaje();

	int getPintado1() { return pintado_1; };
	int getPintado2() { return pintado_2; };

	void aumentaPintado1(int n) { pintado_1 += n ; };
	void aumentaPintado2(int n) { pintado_2 += n ; };
};