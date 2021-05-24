#include "CharactersSelected.h"
#include "Assets/game/GameStateMachine.h"
#include "Assets/sdlutils/SDLUtils.h"

CharactersSelected::CharactersSelected() {
    // Se inicializa el vector de selecci�n a false.
    for (int i = 0; i < numP; ++i) {
        chars.push_back(false);
        chars2.push_back(false);
    }
}

void CharactersSelected::updatePersonaje(Unit pj) {
    if (equipo_ == 0) {
        selectPersonaje(chars, pj);
    }
    else {
        selectPersonaje(chars2, pj);
    }
}

void CharactersSelected::play(GameStateMachine* gsm) {
    if (cont == max)
    {
        int mapa = sdlutils().rand().nextInt(0, 8);
        std::cout << "Numero de mapa: " << mapa << "\n";
        int tileSet = 3;
        if (mapa < 4)
            tileSet = sdlutils().rand().nextInt(1, 3);

        if (gsm->isOnline() && gsm->getNetworkManager()->isMaster())
        {
            std::cout << "Master crear juego: " << mapa << "\n";
            gsm->getNetworkManager()->sendCreateGame(mapa, tileSet);
        }
 
        PlayState* playState = new PlayState(gsm, chars, chars2, mapa, tileSet);
        gsm->changeState(playState);
        gsm->setPlayState(playState);
    }
    else cout << "Play";
}

void CharactersSelected::clientPlay(GameStateMachine* gsm, int mapa, int tileset)
{
    std::cout << "Quiero crear un mapa \n";
    PlayState* playState = new PlayState(gsm, chars, chars2, mapa, tileset);
    gsm->changeState(playState);
    gsm->setPlayState(playState);
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