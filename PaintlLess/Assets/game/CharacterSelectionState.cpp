#include "CharacterSelectionState.h"
#include "PlayState.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../components/MenuButton.h"

#include "GameStateMachine.h"

CharacterSelectionState::CharacterSelectionState(GameStateMachine* gsm) : GameState(gsm) {
	sdlutils().showCursor();

	auto* fondo = mngr_->addEntity(RenderLayer::Fondo);
	fondo->addComponent<Transform>(Vector2D(), sdlutils().width(), sdlutils().height());
	fondo->addComponent<Image>(&sdlutils().images().at("menuSP"));
	auto* ataque = mngr_->addEntity(RenderLayer::Fondo);
	ataque->addComponent<Transform>(Vector2D(0, 0), w + 67, h / 2);
	ataque->addComponent<Image>(&sdlutils().images().at("botonAt"));
	ataque->addComponent<MenuButton>(gsm, personajesAtaque);
	auto* defensa = mngr_->addEntity(RenderLayer::Fondo);
	defensa->addComponent<Transform>(Vector2D(w + 67, 0), w + 67, h / 2);
	defensa->addComponent<Image>(&sdlutils().images().at("botonDef"));
	defensa->addComponent<MenuButton>(gsm, personajesDefensa);
	auto* utilidad = mngr_->addEntity(RenderLayer::Fondo);
	utilidad->addComponent<Transform>(Vector2D(2*(w + 67), 0), w + 67, h / 2);
	utilidad->addComponent<Image>(&sdlutils().images().at("botonUt"));
	utilidad->addComponent<MenuButton>(gsm, personajesUtilidad);
	// Carga todos los botones.
	
	// Falta el sprite.
	auto* Cazador = mngr_->addEntity(RenderLayer::Fondo);
	Cazador->addComponent<Transform>(Vector2D(w / 2, h - 60), w, h);
	Cazador->addComponent<Image>(&sdlutils().images().at("cazadorM"));
	Cazador->addComponent<MenuButton>(gsm, updateCazador);

	auto* Druida = mngr_->addEntity(RenderLayer::Fondo);
<<<<<<< HEAD
	Druida->addComponent<Transform>(Vector2D(w + w / 2, h - 60), w, h);
	Druida->addComponent<Image>(&sdlutils().images().at("druidaM"));
	Druida->addComponent<MenuButton>(gsm, updateDruida);
=======
	Druida->addComponent<Transform>(Vector2D(500, 200), w, h);
	Druida->addComponent<Image>(&sdlutils().images().at("cazador"));
	Druida->addComponent<MenuButton>(gsm, updateCazador);
>>>>>>> 686e2ccfc808a05417cec01d274cafc251bdfe09

	auto* Esqueleto = mngr_->addEntity(RenderLayer::Fondo);
	Esqueleto->addComponent<Transform>(Vector2D(2 * w + w / 2, h - 60), w, h);
	Esqueleto->addComponent<Image>(&sdlutils().images().at("esqueletoM"));
	Esqueleto->addComponent<MenuButton>(gsm, updateEsqueleto);

	auto* Pícara = mngr_->addEntity(RenderLayer::Fondo);
	Pícara->addComponent<Transform>(Vector2D(w / 2, 2 * h - 60), w, h);
	Pícara->addComponent<Image>(&sdlutils().images().at("picaraM"));
	Pícara->addComponent<MenuButton>(gsm, updatePicara);

	auto* Vikingo = mngr_->addEntity(RenderLayer::Fondo);
	Vikingo->addComponent<Transform>(Vector2D(w / 2 + w, 2 * h - 60), w, h);
	Vikingo->addComponent<Image>(&sdlutils().images().at("vikingoM"));
	Vikingo->addComponent<MenuButton>(gsm, updateVikingo);

	auto* Kirin = mngr_->addEntity(RenderLayer::Fondo);
	Kirin->addComponent<Transform>(Vector2D(w / 2 + 2*w, 2 * h - 60), w, h);
	Kirin->addComponent<Image>(&sdlutils().images().at("druidaM"));
	Kirin->addComponent<MenuButton>(gsm, updateKirin);

	

	// Botón de paso de partida.
	auto* Boton = mngr_->addEntity(RenderLayer::Fondo);
	Boton->addComponent<Transform>(Vector2D(700, 500), w, h);
	Boton->addComponent<Image>(&sdlutils().images().at("star"));
	Boton->addComponent<MenuButton>(gsm, play);
}

void CharacterSelectionState::play(GameStateMachine* gsm) { 
	gsm->getCharSel()->play(gsm);
}

// Método que debería enseñar en pantalla los personajes de ataque.
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