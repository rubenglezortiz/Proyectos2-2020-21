#pragma once
#include "GameState.h"
#include "Values.h"
#include <vector>

using namespace std;

/*
* PlayState maneja la partida en curso.
*/

class PlayState : public GameState {

public:
	// Constructora.
   	 PlayState(GameStateMachine* gsm, vector<bool> charss);
	// Destructora.
	 virtual ~PlayState();
	// M�todos que crean a los personajes.
 	 void createBomba();
	 void createDruida();
	 void createEsqueleto();
	 void createGolem();
	 void createKirin();
	 void createTanque();
	 void createPicara();
	 void createVikingo();
	 void createCazador();
};