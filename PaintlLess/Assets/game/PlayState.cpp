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

PlayState::PlayState() : GameState(){
	//auto* fighter = mngr_->addEntity();
	auto* gameMap = mngr_->addEntity(RenderLayer::Fondo);
	//auto* gameMap = mngr_->addEntity();
	gameMap->addComponent<GameMap>("Assets/level1.txt");
	mngr_.get()->setHandler<Mapa>(gameMap);

	Entity* kirin = mngr_->addEntity(RenderLayer::Personajes);
	//Entity* kirin = mngr_->addEntity();
	kirin->addComponent<Transform>(
		Vector2D(0, 0), //Posicion
		Vector2D(),     //Velocidad
		50.0f,          //Ancho
		50.0f,          //Alto
		0.0f);

	kirin->addComponent<Image>(&sdlutils().images().at("kirin"));
	kirin->addComponent<Movimiento>();
	kirin->addComponent<Health>(3, kirin->getComponent<Transform>());
	sdlutils().showCursor();
	kirin->getComponent<Health>()->hit();
	Entity* boardManager = mngr_->addEntity();
	boardManager->addComponent<PointOnImage>(&sdlutils().images().at("selector"));
}

PlayState::~PlayState() {

}