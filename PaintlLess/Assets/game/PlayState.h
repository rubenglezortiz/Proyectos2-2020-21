#pragma once
#include "GameState.h"
#include <vector>

using namespace std;

/*
* PlayState maneja la partida en curso.
*/

class PlayState : public GameState
{
public:
	// Constructora.
   	 PlayState(GameStateMachine* gsm, vector<bool> charss);
	// Destructora.
	 virtual ~PlayState();
	// Métodos que crean a los personajes.
 	 void createBomba();
	 void createDruida();
	 void createEsqueleto();
	 void createGolem();
	 void createKirin();
	 void createTanque();
	 void createPicara();
};