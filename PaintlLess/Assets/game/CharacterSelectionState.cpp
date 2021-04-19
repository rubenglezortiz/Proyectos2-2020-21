#include "CharacterSelectionState.h"
#include "PlayState.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../components/MenuButton.h"
#include "../components/ButtonSelected.h"

#include "GameStateMachine.h"

CharacterSelectionState::CharacterSelectionState(GameStateMachine* gsm) : GameState(gsm) {
	sdlutils().showCursor();

	// FONDO --------------------------------------------------------------
	auto* menuFondo = mngr_->addEntity(RenderLayer::Fondo);
	menuFondo->addComponent<Transform>(Vector2D(), sdlutils().width(), sdlutils().height());
	menuFondo->addComponent<Image>(&sdlutils().images().at("menuSP"));

	// BOTONES ------------------------------------------------------------
	auto* ataque = mngr_->addEntity(RenderLayer::Fondo);
	ataque->addComponent<Transform>(Vector2D(0, 0), 800/3, h / 2);
	ataque->addComponent<Image>(&sdlutils().images().at("botonAt"));
	ataque->addComponent<MenuButton>(gsm, personajesAtaque);

	auto* defensa = mngr_->addEntity(RenderLayer::Fondo);
	defensa->addComponent<Transform>(Vector2D(800/3, 0), 800/3, h / 2);
	defensa->addComponent<Image>(&sdlutils().images().at("botonDef"));
	defensa->addComponent<MenuButton>(gsm, personajesDefensa);

	auto* utilidad = mngr_->addEntity(RenderLayer::Fondo);
	utilidad->addComponent<Transform>(Vector2D(2 * (800/3), 0), 800/3, h / 2);
	utilidad->addComponent<Image>(&sdlutils().images().at("botonUt"));
	utilidad->addComponent<MenuButton>(gsm, personajesUtilidad);

	// PERSONAJES ---------------------------------------------------------
	auto* Alquimista = mngr_->addEntity(RenderLayer::Fondo);
	Alquimista->addComponent<Transform>(Vector2D(0, offset), w, h);
	Alquimista->addComponent<Image>(&sdlutils().images().at("alquimistaSP"));
	Alquimista->addComponent<MenuButton>(gsm, updateAlquimista);
	Alquimista->addComponent<ButtonSelected>(&sdlutils().images().at("alquimistaSP2"));

	auto* Arquitecta = mngr_->addEntity(RenderLayer::Fondo);
	Arquitecta->addComponent<Transform>(Vector2D(w, offset), w, h);
	Arquitecta->addComponent<Image>(&sdlutils().images().at("arquitectaSP"));
	Arquitecta->addComponent<MenuButton>(gsm, updateArquitecta);
	Arquitecta->addComponent<ButtonSelected>(&sdlutils().images().at("arquitectaSP2"));

	auto* Bomba = mngr_->addEntity(RenderLayer::Fondo);
	Bomba->addComponent<Transform>(Vector2D(2 * w, offset), w, h);
	Bomba->addComponent<Image>(&sdlutils().images().at("bombaSP"));
	Bomba->addComponent<MenuButton>(gsm, updateBomba);
	Bomba->addComponent<ButtonSelected>(&sdlutils().images().at("bombaSP2"));

	auto* Cazador = mngr_->addEntity(RenderLayer::Fondo);
	Cazador->addComponent<Transform>(Vector2D(3 * w, offset), w, h);
	Cazador->addComponent<Image>(&sdlutils().images().at("cazadorSP"));
	Cazador->addComponent<MenuButton>(gsm, updateCazador);
	Cazador->addComponent<ButtonSelected>(&sdlutils().images().at("cazadorSP2"));

	auto* Druida = mngr_->addEntity(RenderLayer::Fondo);
	Druida->addComponent<Transform>(Vector2D(4 * w, offset), w, h);
	Druida->addComponent<Image>(&sdlutils().images().at("druidaSP"));
	Druida->addComponent<MenuButton>(gsm, updateDruida);
	Druida->addComponent<ButtonSelected>(&sdlutils().images().at("druidaSP2"));

	auto* Esqueleto = mngr_->addEntity(RenderLayer::Fondo);
	Esqueleto->addComponent<Transform>(Vector2D(w, h + offset), w, h);
	Esqueleto->addComponent<Image>(&sdlutils().images().at("esqueletoSP"));
	Esqueleto->addComponent<MenuButton>(gsm, updateEsqueleto);
	Esqueleto->addComponent<ButtonSelected>(&sdlutils().images().at("esqueletoSP2"));

	auto* Golem = mngr_->addEntity(RenderLayer::Fondo);
	Golem->addComponent<Transform>(Vector2D(2 * w, h + offset), w, h);
	Golem->addComponent<Image>(&sdlutils().images().at("golemSP"));
	Golem->addComponent<MenuButton>(gsm, updateGolem);
	Golem->addComponent<ButtonSelected>(&sdlutils().images().at("golemSP2"));

	auto* Kirin = mngr_->addEntity(RenderLayer::Fondo);
	Kirin->addComponent<Transform>(Vector2D(3 * w, h + offset), w, h);
	Kirin->addComponent<Image>(&sdlutils().images().at("kirinSP"));
	Kirin->addComponent<MenuButton>(gsm, updateKirin);
	Kirin->addComponent<ButtonSelected>(&sdlutils().images().at("kirinSP2"));

	auto* Lobo = mngr_->addEntity(RenderLayer::Fondo);
	Lobo->addComponent<Transform>(Vector2D(0, 2 * h + offset), w, h);
	Lobo->addComponent<Image>(&sdlutils().images().at("loboSP"));
	Lobo->addComponent<MenuButton>(gsm, updateLobo);
	Lobo->addComponent<ButtonSelected>(&sdlutils().images().at("loboSP2"));

	auto* Monaguillo = mngr_->addEntity(RenderLayer::Fondo);
	Monaguillo->addComponent<Transform>(Vector2D(w, 2 * h + offset), w, h);
	Monaguillo->addComponent<Image>(&sdlutils().images().at("monaguilloSP"));
	Monaguillo->addComponent<MenuButton>(gsm, updateMonaguillo);
	Monaguillo->addComponent<ButtonSelected>(&sdlutils().images().at("monaguilloSP2"));

	auto* Picara = mngr_->addEntity(RenderLayer::Fondo);
	Picara->addComponent<Transform>(Vector2D(2 * w, 2 * h + offset), w, h);
	Picara->addComponent<Image>(&sdlutils().images().at("picaraSP"));
	Picara->addComponent<MenuButton>(gsm, updatePicara);
	Picara->addComponent<ButtonSelected>(&sdlutils().images().at("picaraSP2"));

	auto* Tanque = mngr_->addEntity(RenderLayer::Fondo);
	Tanque->addComponent<Transform>(Vector2D(3 * w, 2 * h + offset), w, h);
	Tanque->addComponent<Image>(&sdlutils().images().at("tanqueSP"));
	Tanque->addComponent<MenuButton>(gsm, updateTanque);
	Tanque->addComponent<ButtonSelected>(&sdlutils().images().at("tanqueSP2"));

	auto* Vikingo = mngr_->addEntity(RenderLayer::Fondo);
	Vikingo->addComponent<Transform>(Vector2D(4 * w, 2 * h + offset), w, h);
	Vikingo->addComponent<Image>(&sdlutils().images().at("vikingoSP"));
	Vikingo->addComponent<MenuButton>(gsm, updateVikingo);
	Vikingo->addComponent<ButtonSelected>(&sdlutils().images().at("vikingoSP2"));

	// Botón de paso de partida.
	auto* Boton = mngr_->addEntity(RenderLayer::Fondo);
	Boton->addComponent<Transform>(Vector2D(4*w, h + offset), w, h);
	Boton->addComponent<Image>(&sdlutils().images().at("star"));
	Boton->addComponent<MenuButton>(gsm, play);
}

void CharacterSelectionState::play(GameStateMachine* gsm) { 
	gsm->getCharSel()->play(gsm);
}

void CharacterSelectionState::personajesAtaque(GameStateMachine* gsm) {
	cout << "ataque";
}

// Método que debería enseñar en pantalla los personajes de defensa.
void CharacterSelectionState::personajesDefensa(GameStateMachine* gsm) {
	cout << "defensa";
}

// Método que debería enseñar en pantalla los personajes de utilidad.
void CharacterSelectionState::personajesUtilidad(GameStateMachine* gsm) {
	cout << "utilidad";
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