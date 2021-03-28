#include "PlayState.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../components/GameMap.h"
#include "../components/Movimiento.h"
#include "../components/Health.h"
#include "../components/PointOnImage.h"

#include "../components/MovementShader.h"
#include "GameStateMachine.h"

PlayState::PlayState(GameStateMachine* gsm) : GameState(gsm){

	//Creación gamemap
	auto* gameMap = mngr_->addEntity(RenderLayer::Fondo);

	gameMap->addComponent<GameMap>("Assets/level1.txt");
	mngr_.get()->setHandler<Mapa>(gameMap);


	//cración boardManager
	Entity* boardManager = mngr_->addEntity(RenderLayer::Tablero2);
	boardManager->addComponent<PointOnImage>(&sdlutils().images().at("selector"));
	boardManager->addComponent<MovementShader>(&sdlutils().images().at("selector"));

	mngr_.get()->setHandler<BoardManager>(boardManager);

	//boardManager->getComponent<MovementShader>()->getValues();




	//Creacion personaje
	Entity* kirin = mngr_->addEntity(RenderLayer::Personajes);

	kirin->addComponent<Transform>(
		Vector2D(5, 4), //Posicion
		Vector2D(),     //Velocidad
		50.0f,          //Ancho
		50.0f,          //Alto
		0.0f);

	kirin->addComponent<Image>(&sdlutils().images().at("kirin"));
	kirin->addComponent<Movimiento>();
	kirin->addComponent<Health>(3, kirin->getComponent<Transform>());
	sdlutils().showCursor();
	kirin->getComponent<Health>()->hit();


}

PlayState::~PlayState() {}