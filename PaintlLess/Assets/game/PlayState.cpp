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
#include "../components/Ability_Druid.h"
#include "../components/Attack.h"
#include "../components/DeckSpawn.h"


#include "../components/MovementShader.h"
#include "../game/Values.h"
#include "GameStateMachine.h"

PlayState::PlayState(GameStateMachine* gsm, vector<bool> charss) : GameState(gsm) {

	//Creación gamemap
	auto* m = mngr_->addEntity(RenderLayer::Fondo);		
	m->addComponent<GameMap>("Assets/level1.txt", this);
	mapa = m->getComponent<GameMap>();
	mngr_.get()->setHandler<Mapa>(m);


	//cración boardManager
	Entity* boardManager = mngr_->addEntity(RenderLayer::Tablero2);
	boardManager->addComponent<PointOnImage>(&sdlutils().images().at("selector"));
	boardManager->addComponent<MovementShader>(&sdlutils().images().at("selector"));

	mngr_.get()->setHandler<BoardManager>(boardManager);

	//boardManager->getComponent<MovementShader>()->getValues();

	int x = 2;
	// Crea a los personajes según el vector de personajes que ha recibido.
	for (int i = 0; i < charss.size(); ++i) {
		if (charss[i]) {
			switch (i) {
			case Alquimista:
				//createAlquimista(Primero);
				createMazo(Alquimista, x);
				cout << "alquimista";
				break;
			case Arquitecta:
				//createArquitecta(Primero);
				createMazo(Arquitecta, x);
				cout << "arquitecta";
				break;
			case Bomba:
				//createBomba(Primero);
				createMazo(Bomba, x);
				cout << "bomba";
				break;
			case Cazador:
				//createCazador(Primero);
				createMazo(Cazador, x);
				cout << "cazador";
				break;
			case Druida:
				//createDruida(Primero);
				createMazo(Druida, x);
				cout << "druida";
				break;
			case Esqueleto:
				//createEsqueleto(Primero);
				createMazo(Esqueleto, x);
				cout << "esqueleto";
				break;
			case Golem:
				//createGolem(Primero);
				createMazo(Golem, x);
				cout << "golem";
				break;
			case Kirin:
				//createKirin(Primero);
				createMazo(Kirin, x);
				cout << "kirin";
				break;
			case Lobo:
				//createLobo(Primero);
				createMazo(Lobo, x);
				cout << "lobo";
				break;
			case Monaguillo:
				//createMonaguillo(Primero);
				createMazo(Monaguillo, x);
				cout << "monaguillo";
				break;
			case Picara:
				//createPicara(Primero);
				createMazo(Picara, x);
				cout << "picara";
				break;
			case Tanque:
				//createTanque(Primero);
				createMazo(Tanque, x);
				cout << "tanque";
				break;
			case Vikingo:
				//createVikingo(Primero);
				createMazo(Vikingo, x);
				cout << "vikingo";
				break;
			}
			x++;
		}
		cout << i;
	}
	//createTanque(Segundo);
	sdlutils().showCursor();
	//pasaTurno();
}

PlayState::~PlayState() {}

void PlayState::createMazo(int n, int i) {
		auto* boton = mngr_->addEntity(RenderLayer::Interfaz);
		boton->addComponent<Transform>(Vector2D(i, 9), mapa->getCellWidth(), mapa->getCellHeight());
		
		switch (n) {
		case Alquimista: 
			boton->addComponent<Image>(&sdlutils().images().at("alquimistaSP"));
			boton->addComponent<DeckSpawn>(Alquimista);
			break;
		case Arquitecta:
			boton->addComponent<Image>(&sdlutils().images().at("arquitectaSP"));
			boton->addComponent<DeckSpawn>(Arquitecta);
			break;
		case Bomba:
			boton->addComponent<Image>(&sdlutils().images().at("bombaSP"));
			boton->addComponent<DeckSpawn>(Bomba);
			break;
		case Cazador:
			boton->addComponent<Image>(&sdlutils().images().at("cazadorSP"));
			boton->addComponent<DeckSpawn>(Cazador);
			break;
		case Druida:
			boton->addComponent<Image>(&sdlutils().images().at("druidaSP"));
			boton->addComponent<DeckSpawn>(Druida);
			break;
		case Esqueleto:
			boton->addComponent<Image>(&sdlutils().images().at("esqueletoSP"));
			boton->addComponent<DeckSpawn>(Esqueleto);
			break;
		case Golem:
			boton->addComponent<Image>(&sdlutils().images().at("golemSP"));
			boton->addComponent<DeckSpawn>(Golem);
			break;
		case Kirin:
			boton->addComponent<Image>(&sdlutils().images().at("kirinSP"));
			boton->addComponent<DeckSpawn>(Kirin);
			break;
		case Lobo:
			boton->addComponent<Image>(&sdlutils().images().at("loboSP"));
			boton->addComponent<DeckSpawn>(Lobo);
			break;
		case Monaguillo:
			boton->addComponent<Image>(&sdlutils().images().at("monaguilloSP"));
			boton->addComponent<DeckSpawn>(Monaguillo);
			break;
		case Picara:
			boton->addComponent<Image>(&sdlutils().images().at("picaraSP"));
			boton->addComponent<DeckSpawn>(Picara);
			break;
		case Tanque:
			boton->addComponent<Image>(&sdlutils().images().at("tanqueSP"));
			boton->addComponent<DeckSpawn>(Tanque);
			break;
		case Vikingo:
			boton->addComponent<Image>(&sdlutils().images().at("vikingoSP"));
			boton->addComponent<DeckSpawn>(Vikingo);
			break;
		}	
}


void PlayState::pasaTurno() {
	accionesPorTurno = MAX_ACCIONES;

	if (jugadorActual == Primero) {
		jugadorActual = Segundo;
		if (mana_1 + INCREMENTO_MANA >= MAX_MANA)
			mana_1 = MAX_MANA;
		else
			mana_1 += INCREMENTO_MANA;
	}
	else {
		jugadorActual = Primero;
		if (mana_2 + INCREMENTO_MANA >= MAX_MANA)
			mana_2 = MAX_MANA;
		else
			mana_2 += INCREMENTO_MANA;
	} 
	cout << endl << "MANA_1: " << mana_1 << endl << "MANA_2: " << mana_2 << endl;
	turnosActuales++;
	if (turnosActuales > MAX_TURNOS * 2) cout << "fin de partida\n";

	mngr_->finTurno();
	cout << "Turno pasado\n";

}

bool PlayState::restaMana1(int m)
{
	if (mana_1 - m >= 0) {
		mana_1 -= m;
		return true;
	}
	else
		return false;		
}

bool PlayState::restaMana2(int m)
{
	if (mana_2 - m >= 0) {
		mana_2 -= m;
		return true;
	}
	else
		return false;
}