#pragma once
#include "GameState.h"
#include "Values.h"
#include "../../CharactersSelected.h"
#include <vector>

class GameStateMachine;
class Manager;
using namespace std;

//enum Personajes {Kirin, Druida, Monaguillo, Arquitecto, Alquimista, Tanque, Cazador, Rogue, Lobo, Esqueleto, Vikingo, BombaHumana, Golem};

/*
* CharacterSelectionState maneja el menú de selección de personajes.
*/

class CharacterSelectionState : public GameState 
{
private:
	// Constantes para el ancho y alto de los sprites de los personajes.
	 const int w = 160;
	 const int h = 160;
	 const int offset = 100;

public:
	// Cargamos los botones de los personajes.
	 CharacterSelectionState(GameStateMachine* gsm);
	 ~CharacterSelectionState() {};

	// Método que carga la partida.
	 static void play(GameStateMachine* gsm);

	// Método para mostrar a los personajes seleccionables de cada tipo.
	 static void personajesAtaque(GameStateMachine* gsm);
	 static void personajesDefensa(GameStateMachine* gsm);
	 static void personajesUtilidad(GameStateMachine* gsm);

	// Métodos para seleccionar a los personajes.
	 static void updateAlquimista(GameStateMachine* gsm);
	 static void updateArquitecta(GameStateMachine* gsm);
	 static void updateBomba(GameStateMachine* gsm);
	 static void updateCazador(GameStateMachine* gsm);
	 static void updateDruida(GameStateMachine* gsm);
	 static void updateEsqueleto(GameStateMachine* gsm);
	 static void updateGolem(GameStateMachine* gsm);
	 static void updateKirin(GameStateMachine* gsm);
	 static void updateLobo(GameStateMachine* gsm);
	 static void updateMonaguillo(GameStateMachine* gsm);
	 static void updatePicara(GameStateMachine* gsm);
	 static void updateTanque(GameStateMachine* gsm);
	 static void updateVikingo(GameStateMachine* gsm);
};