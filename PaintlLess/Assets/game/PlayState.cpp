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
#include "../components/MenuButton.h"

#include "../components/MovementShader.h"
#include "../game/Values.h"
#include "FinState.h"
#include "GameStateMachine.h"
#include "Network.h"
#include "../components/EntityFactory.h"

PlayState::PlayState(GameStateMachine* gsm, vector<bool> charss, vector<bool> charss2, int mapa, int tileset) : GameState(gsm) {

	//Obtener net
	net = gsm->getNetworkManager();

	// Creación interfaz
	auto* fondo = mngr_->addEntity(RenderLayer::Fondo);
	fondo->addComponent<Transform>(Vector2D(), sdlutils().width(), sdlutils().height());

	fondo->addComponent<Image>(&sdlutils().images().at("tablero" + to_string(tileset)));

	// Creacion GameMap
	auto* m = mngr_->addEntity(RenderLayer::Tablero);
	m->addComponent<GameMap>(mapa, tileset, this);
	mngr_.get()->setHandler<Mapa>(m);
	mapa_ = m->getComponent<GameMap>();
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

	//boardManager->getComponent<MovementShader>()->getValues();
	mazoEquipo();
	//createTanque(Segundo);
	sdlutils().showCursor();
	//pasaTurno();

	// Creacion Botón pasar turno
	auto* botonTurno = mngr_->addEntity(RenderLayer::Interfaz);
	botonTurno->addComponent<Transform2>(Vector2D(sdlutils().width() - 305, sdlutils().height() - 120), 225, 100);
	botonTurno->addComponent<Image>(&sdlutils().images().at("botonT"));
}

PlayState::~PlayState() {}

void PlayState::mazoEquipo() {
	int x = 1;
	for (int i = 0; i < ch1.size(); ++i) {
		if (ch1[i]) {
			createMazo(i, x, 0);
			x++;
		}
	}
	x = 1;
	for (int i = 0; i < ch2.size(); ++i) {
		if (ch2[i]) {
			createMazo(i, x, 1);
			x++;
		}
	}
}

void PlayState::createMazo(int n, int x, int equipo) {
	if (equipo == 1)
		x = -sdlutils().width();
	auto* boton = mngr_->addEntity(RenderLayer::Personajes);
	boton->addComponent<Transform2>(Vector2D((x + 0.5) * sdlutils().width() / 9, sdlutils().height() - 120), sdlutils().width() / 9, 100);

	std::string imagen;
	if (equipo == 1) imagen = "R";
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
	if (equipo == 1) boton->setGroup<Mazo1>(true);
	else boton->setGroup<Mazo2>(true);
}

void PlayState::moveMazo() {
	int pos = -sdlutils().width();
	float i = 1.5;
	if (jugadorActual == Primero) {
		for (Entity* e : mngr_->getEnteties()) {
			if (e->hasGroup<Mazo2>()) {
				e->getComponent<Transform2>()->getPos().setX(pos);
				pos -= e->getComponent<Transform2>()->getW();
			}
			if (e->hasGroup<Mazo1>()) {
				e->getComponent<Transform2>()->getPos().setX(i * sdlutils().width() / 9);
				i++;
			}
		}
	}
	else {
		for (Entity* e : mngr_->getEnteties()) {
			if (e->hasGroup<Mazo2>()) {
				e->getComponent<Transform2>()->getPos().setX(i * sdlutils().width() / 9);
				i++;
			}
			if (e->hasGroup<Mazo1>()) {
				e->getComponent<Transform2>()->getPos().setX(pos);
				pos -= e->getComponent<Transform2>()->getW();
			}
		}
	}
}

void PlayState::update()
{
	CheckPasarTurno();
	GameState::update();
}

void PlayState::moveChar(Vector2D charPosInMap, Vector2D dest)
{
	//Vector2D aux = mapa_->SDLPointToMapCoords(charPosInMap);
	//std::cout << "PosIni in Map: " << aux.getX() << " " << aux.getY() << "\n";
	//std::cout << "PosIni in SDL: " << charPosInMap.getX() << " " << charPosInMap.getY() << "\n";
	//std::cout << "Dest in Map: " << dest.getX() << " " << dest.getY() << "\n";

	Entity* entity = mapa_->getCharacter(mapa_->SDLPointToMapCoords(charPosInMap));
	if (entity != nullptr)
	{
		Movimiento* movement = entity->getComponent<Movimiento>();
		movement->MoveCharacter(charPosInMap, dest);
	}
	else std::cout << "No deberias estar viendo esto lmao";
}

void PlayState::CheckPasarTurno()
{
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (ih().isKeyDown(SDLK_SPACE) || (mX >= (sdlutils().width() - 330) && mX <= (sdlutils().width() - 330 + 225) && mY >= (sdlutils().height() - 120) && mY <= (sdlutils().height() - 120 + 100) &&
		ih().getMouseButtonState(ih().LEFT))) {
		if (!gameStateMachine->isOnline())
		{
			pasaTurno();
		}
		else if (gameStateMachine->isOnline() &&
			(jugadorActual == Primero && !net->isMaster() ||
				jugadorActual == Segundo && net->isMaster()))
		{
			pasaTurno();
			net->sendChangeTurno();
		}
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
		moveMazo();
	}
	else {
		jugadorActual = Primero;
		if (mana_2 + INCREMENTO_MANA >= MAX_MANA)
			mana_2 = MAX_MANA;
		else
			mana_2 += INCREMENTO_MANA;
		moveMazo();
	}
	cout << endl << "MANA_1: " << mana_1 << endl << "MANA_2: " << mana_2 << endl;

	if (turnosActuales + 1 > MAX_TURNOS * 2) {
		int numCasillasPintables = mapa_->getNumCasPintables();
		int casRojo = getPintado1() * 100 / numCasillasPintables;
		int casAzul = getPintado2() * 100 / numCasillasPintables;
		int ganador, porcentaje;
		if (casRojo > casAzul) {
			ganador = 0;
			porcentaje = casRojo;
		}
		else if (casRojo < casAzul) {
			ganador = 1;
			porcentaje = casAzul;
		}
		else {
			ganador = 2;
			porcentaje = casRojo;
		}
		gameStateMachine->pushState(new FinState(gameStateMachine, ganador, porcentaje));
		cout << "fin de partida\n";
	}

	else turnosActuales++;

	mngr_->finTurno();
	cout << "Turno pasado\n";

}

int PlayState::getPorcentaje() {
	if (jugadorActual == Primero)
		return (pintado_1 * 100) / mapa_->getNumCasPintables();
	else
		return (pintado_2 * 100) / mapa_->getNumCasPintables();
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