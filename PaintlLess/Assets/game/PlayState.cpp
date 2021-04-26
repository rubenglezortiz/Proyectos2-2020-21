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
#include "../components/Interfaz.h"
#include "../components/Transform2.h"


#include "../components/MovementShader.h"
#include "../game/Values.h"
#include "GameStateMachine.h"

PlayState::PlayState(GameStateMachine* gsm, vector<bool> charss, vector<bool> charss2) : GameState(gsm) {

	// Creación imagen fondo.
	auto* fondo = mngr_->addEntity(RenderLayer::Fondo);
	fondo->addComponent<Transform>(Vector2D(), sdlutils().width(), sdlutils().height());
	fondo->addComponent<Image>(&sdlutils().images().at("tablero"));
	
	// Creación gamemap
	auto* m = mngr_->addEntity(RenderLayer::Tablero);		
	m->addComponent<GameMap>("Assets/level1.txt", this);
	mapa = m->getComponent<GameMap>();
	mngr_.get()->setHandler<Mapa>(m);
	m->addComponent<Interfaz>();

	for (int i = 0; i < charss.size(); ++i) {
		if (charss[i]) ch1.push_back(true);
		else ch1.push_back(false);
		if (charss2[i]) ch2.push_back(true);
		else ch2.push_back(false);
	}
	// Creación boardManager
	Entity* boardManager = mngr_->addEntity(RenderLayer::Tablero2);
	boardManager->addComponent<PointOnImage>(&sdlutils().images().at("selector"));
	boardManager->addComponent<MovementShader>(&sdlutils().images().at("selector"));

	mngr_.get()->setHandler<BoardManager>(boardManager);

	mazoEquipo(charss);

	//createTanque(Segundo);
	sdlutils().showCursor();
	//pasaTurno();
}

PlayState::~PlayState() {}

void PlayState::update() {
	if (ih().isKeyDown(SDLK_0)) {
		pasaTurno();
		mngr_->refresh();
	}
	mngr_->update();
	mngr_->refresh();

	sdlutils().clearRenderer();
	mngr_->render();
	sdlutils().presentRenderer();
}
void PlayState::createMazo(int n, int i) {
		auto* boton = mngr_->addEntity(RenderLayer::Interfaz);
		boton->addComponent<Transform2>(Vector2D( i * sdlutils().width() / 9, sdlutils().height() - 100), sdlutils().width() / 9, 70);
		
		std::string imagen;
		if (jugadorActual == Primero) imagen = "R";
		else imagen = "A";

		switch (n) {
		case Alquimista: 
			boton->addComponent<Image>(&sdlutils().images().at("alquimistaMazo" + imagen));
			boton->addComponent<DeckSpawn>(Alquimista);
			break;
		case Arquitecta:
			boton->addComponent<Image>(&sdlutils().images().at("arquitectaMazo" + imagen));
			boton->addComponent<DeckSpawn>(Arquitecta);
			break;
		case Bomba:
			boton->addComponent<Image>(&sdlutils().images().at("bombaMazo" + imagen));
			boton->addComponent<DeckSpawn>(Bomba);
			break;
		case Cazador:
			boton->addComponent<Image>(&sdlutils().images().at("cazadorMazo" + imagen));
			boton->addComponent<DeckSpawn>(Cazador);
			break;
		case Druida:
			boton->addComponent<Image>(&sdlutils().images().at("druidaMazo" + imagen));
			boton->addComponent<DeckSpawn>(Druida);
			break;
		case Esqueleto:
			boton->addComponent<Image>(&sdlutils().images().at("esqueletoMazo" + imagen));
			boton->addComponent<DeckSpawn>(Esqueleto);
			break;
		case Golem:
			boton->addComponent<Image>(&sdlutils().images().at("golemMazo" + imagen));
			boton->addComponent<DeckSpawn>(Golem);
			break;
		case Kirin:
			boton->addComponent<Image>(&sdlutils().images().at("kirinMazo" + imagen));
			boton->addComponent<DeckSpawn>(Kirin);
			break;
		case Lobo:
			boton->addComponent<Image>(&sdlutils().images().at("loboMazo" + imagen));
			boton->addComponent<DeckSpawn>(Lobo);
			break;
		case Monaguillo:
			boton->addComponent<Image>(&sdlutils().images().at("monaguilloMazo" + imagen));
			boton->addComponent<DeckSpawn>(Monaguillo);
			break;
		case Picara:
			boton->addComponent<Image>(&sdlutils().images().at("picaraMazo" + imagen));
			boton->addComponent<DeckSpawn>(Picara);
			break;
		case Tanque:
			boton->addComponent<Image>(&sdlutils().images().at("tanqueMazo" + imagen));
			boton->addComponent<DeckSpawn>(Tanque);
			break;
		case Vikingo:
			boton->addComponent<Image>(&sdlutils().images().at("vikingoMazo" + imagen));
			boton->addComponent<DeckSpawn>(Vikingo);
			break;
		}	
}

void PlayState::freeMazo() {
	for (Entity* e : mngr_->getEnteties()) {
		if (e->getComponent<DeckSpawn>()) e->setActive(false);
	}
}

void PlayState::pasaTurno() {
	accionesPorTurno = MAX_ACCIONES;

	if (jugadorActual == Primero) {
		jugadorActual = Segundo;
		freeMazo();
		mazoEquipo(ch2);
		if (mana_1 + INCREMENTO_MANA >= MAX_MANA)
			mana_1 = MAX_MANA;
		else
			mana_1 += INCREMENTO_MANA;
	}
	else {
		jugadorActual = Primero;
		freeMazo();
		mazoEquipo(ch1);
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

bool PlayState::restaMana(int m, int& mana)
{
	if (mana - m >= 0) {
		mana -= m;
		return true;
	}
	else
		return false;		
}

bool PlayState::manaSuficiente(int m, int mana) const {
	return (mana - m >= 0);
}

void PlayState::mazoEquipo(vector<bool> chars) {
	int x = 0;
	// Crea a los personajes según el vector de personajes que ha recibido.
	for (int i = 0; i < chars.size(); ++i) {
		if (chars[i]) {
			switch (i) {
			case Alquimista:
				createMazo(Alquimista, x);
				cout << "alquimista";
				break;
			case Arquitecta:
				createMazo(Arquitecta, x);
				cout << "arquitecta";
				break;
			case Bomba:
				createMazo(Bomba, x);
				cout << "bomba";
				break;
			case Cazador:
				createMazo(Cazador, x);
				cout << "cazador";
				break;
			case Druida:
				createMazo(Druida, x);
				cout << "druida";
				break;
			case Esqueleto:
				createMazo(Esqueleto, x);
				cout << "esqueleto";
				break;
			case Golem:
				createMazo(Golem, x);
				cout << "golem";
				break;
			case Kirin:
				createMazo(Kirin, x);
				cout << "kirin";
				break;
			case Lobo:
				createMazo(Lobo, x);
				cout << "lobo";
				break;
			case Monaguillo:
				createMazo(Monaguillo, x);
				cout << "monaguillo";
				break;
			case Picara:
				createMazo(Picara, x);
				cout << "picara";
				break;
			case Tanque:
				createMazo(Tanque, x);
				cout << "tanque";
				break;
			case Vikingo:
				createMazo(Vikingo, x);
				cout << "vikingo";
				break;
			}
			x++;
		}
		cout << i;
	}
}