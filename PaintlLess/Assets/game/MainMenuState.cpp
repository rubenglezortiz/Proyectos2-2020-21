#include "MainMenuState.h"
#include "PlayState.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../components/MenuButton.h"
#include "GameStateMachine.h"

MainMenuState::MainMenuState(GameStateMachine* gsm) : GameState(gsm) { //Poner las imagenes y posiciones correctamente
	//Crear botones
	sdlutils().showCursor();
<<<<<<< HEAD

	auto* menuFondo = mngr_->addEntity(RenderLayer::Fondo);
	menuFondo->addComponent<Transform>(Vector2D(0, 0), sdlutils().width(), sdlutils().height());
=======
	
	auto* menuFondo = mngr_->addEntity(RenderLayer::Fondo);
	menuFondo->addComponent<Transform>(Vector2D(0, 0), 800, 600);
>>>>>>> 686e2ccfc808a05417cec01d274cafc251bdfe09
	menuFondo->addComponent<Image>(&sdlutils().images().at("menu"));

	auto* bOnline = mngr_->addEntity(RenderLayer::Fondo);
	bOnline->addComponent<Transform>(Vector2D(325, 200), w, h);
	bOnline->addComponent<Image>(&sdlutils().images().at("start"));
	bOnline->addComponent<MenuButton>(gsm, newGame);

	auto* bLocal = mngr_->addEntity(RenderLayer::Fondo);
	bLocal->addComponent<Transform>(Vector2D(325, 275), w, h);
	bLocal->addComponent<Image>(&sdlutils().images().at("start"));
	bLocal->addComponent<MenuButton>(gsm, newGame);

	auto* bOpc = mngr_->addEntity(RenderLayer::Fondo);
	bOpc->addComponent<Transform>(Vector2D(325, 350), w, h);
	bOpc->addComponent<Image>(&sdlutils().images().at("start"));
	bOpc->addComponent<MenuButton>(gsm, newGame);

	auto* bSalir = mngr_->addEntity(RenderLayer::Fondo);
	bSalir->addComponent<Transform>(Vector2D(325, 425), w, h);
	bSalir->addComponent<Image>(&sdlutils().images().at("star"));
	bSalir->addComponent<MenuButton>(gsm, exitApp);
}

void MainMenuState::newGame(GameStateMachine* gsm) { //Nuevo partida
	
	gsm->pushState(new CharacterSelectionState(gsm));	
}

void MainMenuState::loadGame(GameStateMachine* gsm) { //Cargar partida

}

void MainMenuState::exitApp(GameStateMachine* gsm) { //Salir de la aplicacion	
	ih().setQuit();
}