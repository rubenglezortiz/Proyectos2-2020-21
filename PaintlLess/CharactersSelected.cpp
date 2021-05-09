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
        selectPersonaje(chars, pj);
    }
    else {
        selectPersonaje(chars2, pj);
    }
}

void CharactersSelected::play(GameStateMachine* gsm) {
    if (cont == max) gsm->changeState(new PlayState(gsm, chars, chars2));
    else cout << "Play";
}

void CharactersSelected::selectPersonaje(vector<bool>& ch, Unit pj)
{
    if (!ch[(int)pj] && cont < max) {
        ch[(int)pj] = true;
        cont++;
        cout << "O Selected: ";
    }
    else if (ch[(int)pj]) {
        ch[(int)pj] = false;
        cont--;
        cout << "X Deselected: ";
    }
    else cout << "Can't select any more. ";
}