#include "CharactersSelected.h"
#include "Assets/game/GameStateMachine.h"

CharactersSelected::CharactersSelected() {
	// Se inicializa el vector de selección a false.
	for (int i = 0; i < numP; ++i) {
		chars.push_back(false);
		chars2.push_back(false);
	}
}

void CharactersSelected::updatePersonaje(Unit pj) {
	if (equipo == 0) {
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
	else {
		if (!chars2[pj] && cont2 < max) {
			chars2[pj] = true;
			cont2++;
			cout << "O Selected: ";
		}
		else if (chars2[pj]) {
			chars[pj] = false;
			cont2--;
			cout << "X Deselected: ";
		}
		else cout << "Can't select any more. ";
	}
}

void CharactersSelected::play(GameStateMachine* gsm) {
	if (cont == max) gsm->pushState(new PlayState(gsm, chars, chars2));
	else cout << "Play";
}