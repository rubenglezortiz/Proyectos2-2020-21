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

	auto* Arquitecta = mngr_->addEntity(RenderLayer::Fondo);
	Arquitecta->addComponent<Transform>(Vector2D(200, 400), w, h);
	Arquitecta->addComponent<Image>(&sdlutils().images().at("golem"));
	Arquitecta->addComponent<MenuButton>(gsm, updateArquitecta);

	auto* Bomba = mngr_->addEntity(RenderLayer::Fondo);
	Bomba->addComponent<Transform>(Vector2D(300, 300), w, h);
	Bomba->addComponent<Image>(&sdlutils().images().at("bomba"));
	Bomba->addComponent<MenuButton>(gsm, updateBomba);

	// Falta el sprite.
	auto* Cazador = mngr_->addEntity(RenderLayer::Fondo);
	Cazador->addComponent<Transform>(Vector2D(400, 300), w, h);
	Cazador->addComponent<Image>(&sdlutils().images().at("cazador"));
	Cazador->addComponent<MenuButton>(gsm, updateCazador);

	auto* Druida = mngr_->addEntity(RenderLayer::Fondo);
	Druida->addComponent<Transform>(Vector2D(500, 200), w, h);
	Druida->addComponent<Image>(&sdlutils().images().at("cazador"));
	Druida->addComponent<MenuButton>(gsm, updateCazador);

	auto* Esqueleto = mngr_->addEntity(RenderLayer::Fondo);
	Esqueleto->addComponent<Transform>(Vector2D(400, 200), w, h);
	Esqueleto->addComponent<Image>(&sdlutils().images().at("esqueleto"));
	Esqueleto->addComponent<MenuButton>(gsm, updateEsqueleto);

	auto* Golem = mngr_->addEntity(RenderLayer::Fondo);
	Cazador->addComponent<Transform>(Vector2D(600, 400), w, h);
	Cazador->addComponent<Image>(&sdlutils().images().at("golem"));
	Cazador->addComponent<MenuButton>(gsm, updateGolem);

	auto* Kirin = mngr_->addEntity(RenderLayer::Fondo);
	Kirin->addComponent<Transform>(Vector2D(200, 200), w, h);
	Kirin->addComponent<Image>(&sdlutils().images().at("kirin"));
	Kirin->addComponent<MenuButton>(gsm, updateKirin);

	// Falta el sprite.
	auto* Lobo = mngr_->addEntity(RenderLayer::Fondo);
	Lobo->addComponent<Transform>(Vector2D(300, 400), w, h);
	Lobo->addComponent<Image>(&sdlutils().images().at("golem"));
	Lobo->addComponent<MenuButton>(gsm, updateLobo);

	// Falta el sprite.
	auto* Monaguillo = mngr_->addEntity(RenderLayer::Fondo);
	Monaguillo->addComponent<Transform>(Vector2D(500, 300), w, h);
	Monaguillo->addComponent<Image>(&sdlutils().images().at("life"));
	Monaguillo->addComponent<MenuButton>(gsm, updateMonaguillo);

	auto* Picara = mngr_->addEntity(RenderLayer::Fondo);
	Picara->addComponent<Transform>(Vector2D(600, 200), w, h);
	Picara->addComponent<Image>(&sdlutils().images().at("picara"));
	Picara->addComponent<MenuButton>(gsm, updatePicara);

	auto* Tanque = mngr_->addEntity(RenderLayer::Fondo);
	Tanque->addComponent<Transform>(Vector2D(300, 200), w, h);
	Tanque->addComponent<Image>(&sdlutils().images().at("tanque"));
	Tanque->addComponent<MenuButton>(gsm, updateTanque);

	// Falta el sprite.
	auto* Vikingo = mngr_->addEntity(RenderLayer::Fondo);
	Vikingo->addComponent<Transform>(Vector2D(500, 400), w, h);
	Vikingo->addComponent<Image>(&sdlutils().images().at("golem"));
	Vikingo->addComponent<MenuButton>(gsm, updateVikingo);

	// Botón de paso de partida.
	auto* Boton = mngr_->addEntity(RenderLayer::Fondo);
	Boton->addComponent<Transform>(Vector2D(700, 500), w, h);
	Boton->addComponent<Image>(&sdlutils().images().at("star"));
	Boton->addComponent<MenuButton>(gsm, play);
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