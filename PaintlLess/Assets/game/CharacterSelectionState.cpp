#include "CharacterSelectionState.h"
#include "PlayState.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../components/MenuButton.h"

#include "GameStateMachine.h"

CharacterSelectionState::CharacterSelectionState(GameStateMachine* gsm) : GameState(gsm) {
	sdlutils().showCursor();

	// Carga todos los botones.
	auto* Alquimista = mngr_->addEntity(RenderLayer::Fondo);
	Alquimista->addComponent<Transform>(Vector2D(400, 400), w, h);
	Alquimista->addComponent<Image>(&sdlutils().images().at("golem"));
	Alquimista->addComponent<MenuButton>(gsm, updateAlquimista);

}

void CharacterSelectionState::play(GameStateMachine* gsm) { 
	gsm->getCharSel()->play(gsm);
}

// ALQUIMISTA
void CharacterSelectionState::updateAlquimista(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Alquimista);
	cout << "Alquimista " << endl;
}

// ARQUITECTA
void CharacterSelectionState::updateArquitecta(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Arquitecta);
	cout << "Arquitecta " << endl;
}

// BOMBA
void CharacterSelectionState::updateBomba(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Bomba);
	cout << "Bomba " << endl;
}

// CAZADOR
void CharacterSelectionState::updateCazador(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Cazador);
	cout << "Cazador " << endl;
}

// DRUIDA
void CharacterSelectionState::updateDruida(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Druida);
	cout << "Druida " << endl;
}

// ESQUELETO
void CharacterSelectionState::updateEsqueleto(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Esqueleto);
	cout << "Esqueleto " << endl;
}

// GOLEM
void CharacterSelectionState::updateGolem(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Golem);
	cout << "Golem " << endl;
}

// KIRIN
void CharacterSelectionState::updateKirin(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Kirin);
	cout << "Kirin " << endl;
}

// LOBO
void CharacterSelectionState::updateLobo(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Lobo);
	cout << "Lobo " << endl;
}

// MONAGUILLO
void CharacterSelectionState::updateMonaguillo(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Monaguillo);
	cout << "Monaguillo " << endl;
}

// PICARA
void CharacterSelectionState::updatePicara(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Picara);
	cout << "Picara " << endl;
}

// TANQUE
void CharacterSelectionState::updateTanque(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Tanque);
	cout << "Tanque " << endl;
}

// VIKINGO
void CharacterSelectionState::updateVikingo(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Vikingo);
	cout << "Vikingo " << endl;
}