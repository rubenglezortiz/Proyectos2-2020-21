#pragma once
#include <vector>
#include "Assets/game/Values.h"
#include "Assets/game/PlayState.h"

#include <iostream>
using namespace std;

class GameStateMachine; 

/*
* CharactersSelected gestiona los personajes seleccionados en el men� de selecci�n de personaje.
*/
class CharactersSelected
{
private:
	// M�ximo de personajes en la baraja.
	 const int max = 6;
	// N�mero total de personajes presentados.
	 const int numP = 13;
	 // Vector que mantiene la selecci�n de los personajes del jugador 1.
	 vector<bool> chars;
	 // Vector que mantiene la selecci�n de los personajes del jugador 2.
	 vector<bool> chars2;
	 // Contador de personajes seleccionados del jugador 1.
	 int cont = 0;
	 // Contador de personajes seleccionados del jugador 2.
	 int cont2 = 0;
	 int equipo = 0;
public:
	// Constructora.
	 CharactersSelected();
	// Destructora.
	 ~CharactersSelected() { }
	// M�todo que selecciona/deselecciona un personaje.
	 void updatePersonaje(Unit pj);
	// M�todo que pasa a la partida cuando se han seleccionado max personajes.
	 void play(GameStateMachine* gsm);

	 void siguienteEquipo() { equipo++; }
	 int getCont() { if (equipo == 0) return cont; else return cont2; }
	 int getEquipo() { return equipo; }
	 int getMax() { return max; }
};

