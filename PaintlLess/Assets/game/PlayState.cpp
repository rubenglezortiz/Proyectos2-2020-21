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
#include "../components/Ability_Architect.h"
#include "../components/Ability_Bomb.h"
#include "../components/Ability_Golem.h"
#include "../components/Ability_Rogue.h"
#include "../components/Ability_Viking.h"
#include "../components/Attack.h"

#include "../components/MovementShader.h"
#include "GameStateMachine.h"

PlayState::PlayState(GameStateMachine* gsm, vector<bool> charss) : GameState(gsm){

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
	
	
	// Crea a los personajes según el vector de personajes que ha recibido.
	for (int i = 0; i < charss.size(); ++i) {
		if (charss[i]) {
			switch (i) {
			case Alquimista:
				//createAlquimista();
				cout << "alquimista";
				break;
			case Arquitecta:
				//createArquitecta();
				cout << "arquitecta";
				break;
			case Bomba:
				createBomba();
				cout << "bomba";
				break;
			case Cazador:
				//createCazador();
				cout << "cazador";
				break;
			case Druida:
				createDruida();
				cout << "druida";
				break;
			case Esqueleto:
				createEsqueleto();
				cout << "esqueleto";
				break;
			case Golem:
				createGolem();
				cout << "golem";
				break;
			case Kirin:
				createKirin();
				cout << "kirin";
				break;
			case Lobo:
				//createLobo();
				cout << "lobo";
				break;
			case Monaguillo:
				//createMonaguillo();
				cout << "monaguillo";
				break;
			case Picara:
				createPicara();
				cout << "picara";
				break;
			case Tanque:
				createTanque();
				cout << "tanque";
				break;
			case Vikingo:
				//createVikingo();
				cout << "vikingo";
				break;
			}
		}
		
		cout << i;
	}


	//Entity* kirin2 = mngr_->addEntity(RenderLayer::Personajes);

	//kirin2->addComponent<Transform>(
	//	Vector2D(1, 0), //Posicion
	//	Vector2D(),     //Velocidad
	//	50.0f,          //Ancho
	//	50.0f,          //Alto
	//	0.0f);

	//kirin2->addComponent<Image>(&sdlutils().images().at("kirin"));
	//kirin2->addComponent<Movimiento>();
	//kirin2->addComponent<Health>(1, kirin->getComponent<Transform>());
	//kirin2->getComponent<Health>()->hit();

}

PlayState::~PlayState() {}

// BOMBA
void PlayState::createBomba() {
	Entity* bomba = mngr_->addEntity(RenderLayer::Personajes);
	bomba->addComponent<Transform>(Vector2D(0, 4), Vector2D(), 50.0f, 50.0f, 0.0f);
	bomba->addComponent<Image>(&sdlutils().images().at("bomba"));
	bomba->addComponent<Movimiento>();
	bomba->addComponent<Ability_Bomb>();
	bomba->addComponent<Health>(3);
	sdlutils().showCursor();
}

// DRUIDA
void PlayState::createDruida() {
	Entity* druida = mngr_->addEntity(RenderLayer::Personajes);
	druida->addComponent<Transform>(Vector2D(0, 2), Vector2D(), 50.0f, 50.0f, 0.0f);
	druida->addComponent<Image>(&sdlutils().images().at("druida"));
	druida->addComponent<Movimiento>();
	druida->addComponent<Ability_Viking>();
	druida->addComponent<Health>(3);
	sdlutils().showCursor();
}

// ESQUELETO
void PlayState::createEsqueleto() {
	Entity* esqueleto = mngr_->addEntity(RenderLayer::Personajes);
	esqueleto->addComponent<Transform>(Vector2D(0, 6), Vector2D(), 50.0f, 50.0f, 0.0f);
	esqueleto->addComponent<Image>(&sdlutils().images().at("esqueleto"));
	esqueleto->addComponent<Movimiento>();
	esqueleto->addComponent<Health>(3);
	sdlutils().showCursor();
}

// GOLEM
void PlayState::createGolem() {
	Entity* golem = mngr_->addEntity(RenderLayer::Personajes);
	golem->addComponent<Transform>(Vector2D(0, 5), Vector2D(), 50.0f, 50.0f, 0.0f);
	golem->addComponent<Image>(&sdlutils().images().at("golem"));
	golem->addComponent<Movimiento>();
	golem->addComponent<Health>(3);
	sdlutils().showCursor();
}

// KIRIN
void PlayState::createKirin() {
	Entity* kirin = mngr_->addEntity(RenderLayer::Personajes);
	kirin->addComponent<Transform>(Vector2D(0, 0), Vector2D(), 50.0f, 50.0f, 0.0f);
	kirin->addComponent<Image>(&sdlutils().images().at("kirin"));
	kirin->addComponent<Movimiento>();
	kirin->addComponent<Ability_Golem>();
	kirin->addComponent<Health>(3);
	sdlutils().showCursor();
}

// PICARA
void PlayState::createPicara() {
	Entity* picara = mngr_->addEntity(RenderLayer::Personajes);
	picara->addComponent<Transform>(Vector2D(0, 3), Vector2D(), 50.0f, 50.0f, 0.0f);
	picara->addComponent<Image>(&sdlutils().images().at("picara"));
	picara->addComponent<Movimiento>();
	picara->addComponent<Health>(3);
	picara->addComponent<Attack>();
	picara->addComponent<Ability_Rogue>();
	sdlutils().showCursor();
}

// TANQUE
void PlayState::createTanque() {
	Entity* tanque = mngr_->addEntity(RenderLayer::Personajes);
	tanque->addComponent<Transform>(Vector2D(0, 1),Vector2D(), 50.0f, 50.0f, 0.0f);
	tanque->addComponent<Image>(&sdlutils().images().at("tanque"));
	tanque->addComponent<Movimiento>();
	tanque->addComponent<Health>(3);
	sdlutils().showCursor();
}