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
	// Métodos que crean a los personajes.
	 void createAlquimista();
	 void createArquitecta();
	 void createBomba();
	 void createCazador();
	 void createDruida();
	 void createEsqueleto();
	 void createGolem();
	 void createKirin();
	 void createLobo();
	 void createMonaguillo();
	 void createTanque();
	 void createPicara();
<<<<<<< HEAD
	 void createVikingo();
=======
	 void createCazador();
>>>>>>> 686e2ccfc808a05417cec01d274cafc251bdfe09
};