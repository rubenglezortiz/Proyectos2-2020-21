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
#include "../components/Ability_Kirin.h"
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
				createAlquimista(Primero);
				cout << "alquimista";
				break;
			case Arquitecta:
				createArquitecta(Primero);
				cout << "arquitecta";
				break;
			case Bomba:
				createBomba(Primero);
				cout << "bomba";
				break;
			case Cazador:
				createCazador(Primero);
				cout << "cazador";
				break;
			case Druida:
				createDruida(Primero);
				cout << "druida";
				break;
			case Esqueleto:
				createEsqueleto(Primero);
				cout << "esqueleto";
				break;
			case Golem:
				createGolem(Primero);
				cout << "golem";
				break;
			case Kirin:
				createKirin(Primero);
				cout << "kirin";
				break;
			case Lobo:
				createLobo(Primero);
				cout << "lobo";
				break;
			case Monaguillo:
				createMonaguillo(Primero);
				cout << "monaguillo";
				break;
			case Picara:
				createPicara(Primero);
				cout << "picara";
				break;
			case Tanque:
				createTanque(Primero);
				cout << "tanque";
				break;
			case Vikingo:
				createVikingo(Primero);
				cout << "vikingo";
				break;
			}
		}
		
		cout << i;

	}

	createTanque(Segundo);
	//pasaTurno();


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

// ALQUIMISTA
void PlayState::createAlquimista(Equipo c) {
	Entity* alquimista = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) alquimista->setGroup<Equipo_Rojo>(alquimista);
	else alquimista->setGroup<Equipo_Azul>(alquimista);
	alquimista->addComponent<Transform>(Vector2D(0, 0), Vector2D(), 50.0f, 50.0f, 0.0f);
	alquimista->addComponent<Image>(&sdlutils().images().at("alquimista"));
	alquimista->addComponent<Movimiento>(this);
	alquimista->addComponent<Health>(3);
	sdlutils().showCursor();
}

// ARQUITECTA
void PlayState::createArquitecta(Equipo c) {
	Entity* arquitecta = mngr_->addEntity(RenderLayer::Personajes);

	if (c == Primero) arquitecta->setGroup<Equipo_Rojo>(arquitecta);
	else arquitecta->setGroup<Equipo_Azul>(arquitecta);
	arquitecta->addComponent<Transform>(Vector2D(0, 1), Vector2D(), 50.0f, 50.0f, 0.0f);
	arquitecta->addComponent<Image>(&sdlutils().images().at("arquitecta"));
	arquitecta->addComponent<Movimiento>(this);
	arquitecta->addComponent<Ability_Architect>();
	arquitecta->addComponent<Health>(3);
	arquitecta->addComponent<Attack>();
	sdlutils().showCursor();
}

// BOMBA
void PlayState::createBomba(Equipo c) {
	Entity* bomba = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) bomba->setGroup<Equipo_Rojo>(bomba);
	else bomba->setGroup<Equipo_Azul>(bomba);
	bomba->addComponent<Transform>(Vector2D(0, 2), Vector2D(), 50.0f, 50.0f, 0.0f);
	bomba->addComponent<Image>(&sdlutils().images().at("bomba"));
	bomba->addComponent<Movimiento>(this);
	bomba->addComponent<Ability_Bomb>();
	bomba->addComponent<Health>(3);
	bomba->addComponent<Attack>();
	sdlutils().showCursor();
}

// CAZADOR
void PlayState::createCazador(Equipo c) {
	Entity* cazador = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) cazador->setGroup<Equipo_Rojo>(cazador);
	else cazador->setGroup<Equipo_Azul>(cazador);
	cazador->addComponent<Transform>(Vector2D(0, 3), Vector2D(), 50.0f, 50.0f, 0.0f);
	cazador->addComponent<Image>(&sdlutils().images().at("cazador"));
	cazador->addComponent<Movimiento>(this);
	cazador->addComponent<Health>(3);
	cazador->addComponent<Attack>();
	sdlutils().showCursor();
}

// DRUIDA
void PlayState::createDruida(Equipo c) {
	Entity* druida = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) druida->setGroup<Equipo_Rojo>(druida);
	else druida->setGroup<Equipo_Azul>(druida);
	druida->addComponent<Transform>(Vector2D(0, 4), Vector2D(), 50.0f, 50.0f, 0.0f);
	druida->addComponent<Image>(&sdlutils().images().at("druida"));
	druida->addComponent<Movimiento>(this);
	druida->addComponent<Health>(3);
	druida->addComponent<Attack>();
	sdlutils().showCursor();
}

// ESQUELETO
void PlayState::createEsqueleto(Equipo c) {
	Entity* esqueleto = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) esqueleto->setGroup<Equipo_Rojo>(esqueleto);
	else esqueleto->setGroup<Equipo_Azul>(esqueleto);
	esqueleto->addComponent<Transform>(Vector2D(0, 5), Vector2D(), 50.0f, 50.0f, 0.0f);
	esqueleto->addComponent<Image>(&sdlutils().images().at("esqueleto"));
	esqueleto->addComponent<Movimiento>(this);
	esqueleto->addComponent<Health>(3);
	esqueleto->addComponent<Attack>();
	sdlutils().showCursor();
}

// GOLEM
void PlayState::createGolem(Equipo c) {
	Entity* golem = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) golem->setGroup<Equipo_Rojo>(golem);
	else golem->setGroup<Equipo_Azul>(golem);
	golem->addComponent<Transform>(Vector2D(0, 6), Vector2D(), 50.0f, 50.0f, 0.0f);
	golem->addComponent<Image>(&sdlutils().images().at("golem"));
	golem->addComponent<Ability_Golem>();
	golem->addComponent<Health>(3);
	golem->addComponent<Attack>();
	sdlutils().showCursor();
}

// KIRIN
void PlayState::createKirin(Equipo c) {
	Entity* kirin = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) kirin->setGroup<Equipo_Rojo>(kirin);
	else kirin->setGroup<Equipo_Azul>(kirin);
	kirin->addComponent<Transform>(Vector2D(0, 7), Vector2D(), 50.0f, 50.0f, 0.0f);
	kirin->addComponent<Image>(&sdlutils().images().at("monaguillo"));
	kirin->addComponent<Movimiento>(this);
	kirin->addComponent<Health>(3);
	kirin->addComponent<Attack>();
	kirin->addComponent<Ability_Kirin>();
	sdlutils().showCursor();
}

// LOBO
void PlayState::createLobo(Equipo c) {
	Entity* lobo = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) lobo->setGroup<Equipo_Rojo>(lobo);
	else lobo->setGroup<Equipo_Azul>(lobo);
	lobo->addComponent<Transform>(Vector2D(0, 8), Vector2D(), 50.0f, 50.0f, 0.0f);
	lobo->addComponent<Image>(&sdlutils().images().at("lobo"));
	lobo->addComponent<Movimiento>(this);
	lobo->addComponent<Health>(3);
	lobo->addComponent<Attack>();
	sdlutils().showCursor();
}

// MONAGUILLO
void PlayState::createMonaguillo(Equipo c) {
	Entity* monaguillo = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) monaguillo->setGroup<Equipo_Rojo>(monaguillo);
	else monaguillo->setGroup<Equipo_Azul>(monaguillo);
	monaguillo->addComponent<Transform>(Vector2D(2, 0), Vector2D(), 50.0f, 50.0f, 0.0f);
	monaguillo->addComponent<Image>(&sdlutils().images().at("monaguillo"));
	monaguillo->addComponent<Movimiento>(this);
	monaguillo->addComponent<Health>(3);
	monaguillo->addComponent<Attack>();
	sdlutils().showCursor();
}

// PICARA
void PlayState::createPicara(Equipo c) {
	Entity* picara = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) picara->setGroup<Equipo_Rojo>(picara);
	else picara->setGroup<Equipo_Azul>(picara);
	picara->addComponent<Transform>(Vector2D(1, 0), Vector2D(), 50.0f, 50.0f, 0.0f);
	picara->addComponent<Image>(&sdlutils().images().at("picara"));
	picara->addComponent<Movimiento>(this);
	picara->addComponent<Health>(3);
	picara->addComponent<Ability_Rogue>();
	picara->addComponent<Attack>();
	sdlutils().showCursor();
}

// TANQUE
void PlayState::createTanque(Equipo c) {
	Entity* tanque = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) {
		tanque->setGroup<Equipo_Rojo>(tanque);
		tanque->addComponent<Transform>(Vector2D(1, 1), Vector2D(), 50.0f, 50.0f, 0.0f);
	}
	else {
		tanque->setGroup<Equipo_Azul>(tanque);
		tanque->addComponent<Transform>(Vector2D(8, 1), Vector2D(), 50.0f, 50.0f, 0.0f);
	}
	tanque->addComponent<Image>(&sdlutils().images().at("tanque"));
	tanque->addComponent<Movimiento>(this);
	tanque->addComponent<Health>(3);
	tanque->addComponent<Attack>();
	sdlutils().showCursor();
}

// VIKINGO
void PlayState::createVikingo(Equipo c) {
	Entity* vikingo = mngr_->addEntity(RenderLayer::Personajes);
	if (c == Primero) vikingo->setGroup<Equipo_Rojo>(vikingo);
	else vikingo->setGroup<Equipo_Azul>(vikingo);
	vikingo->addComponent<Transform>(Vector2D(1, 2), Vector2D(), 50.0f, 50.0f, 0.0f);
	vikingo->addComponent<Image>(&sdlutils().images().at("vikingo"));
	vikingo->addComponent<Movimiento>(this);
	vikingo->addComponent<Health>(3);
	vikingo->addComponent<Ability_Viking>();
	vikingo->addComponent<Attack>();
	sdlutils().showCursor();
}






void PlayState::pasaTurno() {
	accionesPorTurno = MAX_ACCIONES;
	if (jugadorActual == Primero)jugadorActual = Segundo;
	else jugadorActual = Primero;
	
	turnosActuales++;
	if (turnosActuales > MAX_TURNOS*2) cout << "fin de partida\n";

	cout << "Turno pasado\n";

}