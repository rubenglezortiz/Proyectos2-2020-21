#include "CharactersSelected.h"
#include "Assets/game/GameStateMachine.h"

CharactersSelected::CharactersSelected() {
	// Se inicializa el vector de selección a false.
	for (int i = 0; i < numP; ++i) {
		chars.push_back(false);
	}
}

void CharactersSelected::updatePersonaje(Unit pj) {
	if (!chars[pj] && cont < max) {
		chars[pj] = true;
		cont++;
		cout << "O Selected: ";
	}
	else if (chars[pj]) {
		chars[pj] = false;
		cont--;
		cout << "X Deselected: ";
	}
	else cout << "Can't select any more. ";
}

void CharactersSelected::play(GameStateMachine* gsm) {
	if (cont == max) gsm->pushState(new PlayState(gsm, chars));
	else cout << "Play";
}