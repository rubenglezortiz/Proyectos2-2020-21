#include "MainMenuState.h"
#include "PlayState.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../components/MenuButton.h"
#include "../components/ButtonHovered.h"
#include "GameStateMachine.h"

MainMenuState::MainMenuState(GameStateMachine* gsm) : GameState(gsm) { //Poner las imagenes y posiciones correctamente
	//Crear botones
	sdlutils().showCursor();

	auto* menuFondo = mngr_->addEntity(RenderLayer::Fondo);
	menuFondo->addComponent<Transform>(Vector2D(0, 0), sdlutils().width(), sdlutils().height());
	menuFondo->addComponent<Image>(&sdlutils().images().at("menu"));

	auto* bOnline = mngr_->addEntity(RenderLayer::Fondo);
	bOnline->addComponent<Transform>(Vector2D(325, 200), w, h);
	bOnline->addComponent<Image>(&sdlutils().images().at("online1"));
	bOnline->addComponent<MenuButton>(gsm, newGame, "menuInicioSound");
	bOnline->addComponent<ButtonHovered>(&sdlutils().images().at("online2"));

	auto* bLocal = mngr_->addEntity(RenderLayer::Fondo);
	bLocal->addComponent<Transform>(Vector2D(325, 300), w, h);
	bLocal->addComponent<Image>(&sdlutils().images().at("local1"));
	bLocal->addComponent<MenuButton>(gsm, newGame, "menuInicioSound");
	bLocal->addComponent<ButtonHovered>(&sdlutils().images().at("local2"));

	auto* bOpc = mngr_->addEntity(RenderLayer::Fondo);
	bOpc->addComponent<Transform>(Vector2D(325, 400), w + 45, h);
	bOpc->addComponent<Image>(&sdlutils().images().at("opciones1"));
	bOpc->addComponent<MenuButton>(gsm, newGame, "menuInicioSound");
	bOpc->addComponent<ButtonHovered>(&sdlutils().images().at("opciones2"));

	auto* bSalir = mngr_->addEntity(RenderLayer::Fondo);
	bSalir->addComponent<Transform>(Vector2D(325, 500), w, h);
	bSalir->addComponent<Image>(&sdlutils().images().at("salir1"));
	bSalir->addComponent<MenuButton>(gsm, exitApp);
	bSalir->addComponent<ButtonHovered>(&sdlutils().images().at("salir2"));
}

void MainMenuState::newGame(GameStateMachine* gsm) { //Nuevo partida
	
	gsm->pushState(new CharacterSelectionState(gsm));	
}

void MainMenuState::loadGame(GameStateMachine* gsm) { //Cargar partida

}

void MainMenuState::exitApp(GameStateMachine* gsm) { //Salir de la aplicacion	
	ih().setQuit();
}