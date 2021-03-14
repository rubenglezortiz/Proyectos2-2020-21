// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "..\GameMap.h"

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("PaintLess", 800, 600,
		"resources/config/resources.json");

	//auto* fighter = mngr_->addEntity();
	auto* gameMap = mngr_->addEntity();
	gameMap->addComponent<GameMap>("Assets/level1.txt");

	
	

	Entity* kirin = mngr_->addEntity();
	kirin->addComponent<Transform>(
		Vector2D(5, 6), //Posicion
		Vector2D(),                                                      //Velocidad
		50.0f,                                                              //Ancho
		50.0f,                                                              //Alto
		0.0f);

	kirin->addComponent<Image>(&sdlutils().images().at("kirin"));
	mngr_.get()->setHandler<Mapa>(kirin);
	sdlutils().showCursor();
	

}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->update();
		mngr_->refresh();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();


		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

