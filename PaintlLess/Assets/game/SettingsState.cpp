#include "SettingsState.h"
#include "PlayState.h"
#include "FinState.h"
#include "../components/Image.h"
#include "../components/Transform2.h"
#include "../components/Transform.h"
#include "../components/ButtonVolume.h"
#include "../components/ButtonSettings.h"
#include "../components/ButtonSurrender.h"
#include "../components/ButtonTick.h"
#include "../components/MenuButton.h"
#include "../game/GameStateMachine.h"
#include "../game/ControlState.h"

SettingsState::SettingsState(GameStateMachine* gsm, PlayState* pS) : GameState(gsm) {
	auto* fondo = mngr_->addEntity(RenderLayer::Fondo);
	fondo->addComponent<Transform2>(Vector2D(0, 0), sdlutils().width(), sdlutils().height());
	fondo->addComponent<Image>(&sdlutils().images().at("fondo"));

	auto* barra = mngr_->addEntity(RenderLayer::Interfaz);
	barra->addComponent<Transform2>(Vector2D(sdlutils().width() / 2 - 450, sdlutils().height() - 150), 900, 75);
	barra->addComponent<Image>(&sdlutils().images().at("barraVolumen"));

	auto* volumen = mngr_->addEntity(RenderLayer::Interfaz);
	volumen->addComponent<Transform2>(Vector2D(sdlutils().volume() * 8 + (sdlutils().width() / 2 - 400), sdlutils().height() - 150), 75, 75);
	volumen->addComponent<Image>(&sdlutils().images().at("botonVolumen"));
	volumen->addComponent<ButtonVolume>();

	auto* botonX = mngr_->addEntity(RenderLayer::Interfaz);
	botonX->addComponent<Transform>(Vector2D(sdlutils().width() - 150, 0), 150, 150);
	botonX->addComponent<Image>(&sdlutils().images().at("botonAtras"));
	botonX->addComponent<MenuButton>(gsm, goBack);

	auto* botonTick = mngr_->addEntity(RenderLayer::Interfaz);
	botonTick->addComponent<Transform2>(Vector2D(sdlutils().width() - 600, 100), 125, 125);
	botonTick->addComponent<Image>(&sdlutils().images().at("tick1"));
	botonTick->addComponent<ButtonTick>(&sdlutils().images().at("tick2"), tickVolume);

	auto* botonTick2 = mngr_->addEntity(RenderLayer::Interfaz);
	botonTick2->addComponent<Transform2>(Vector2D(sdlutils().width() - 600, 300), 125, 125);
	botonTick2->addComponent<Image>(&sdlutils().images().at("tick1"));
	botonTick2->addComponent<ButtonTick>(&sdlutils().images().at("tick2"), tickVolume);

	auto* botonControles = mngr_->addEntity(RenderLayer::Interfaz);
	botonControles->addComponent<Transform>(Vector2D(sdlutils().width() - 600, sdlutils().height() / 2 + 145), 125, 125);
	botonControles->addComponent<Image>(&sdlutils().images().at("mando"));
	botonControles->addComponent<MenuButton>(gsm, goControles);

	if (pS != nullptr) {
		playState_ = pS;
		auto* bRendirse = mngr_->addEntity(RenderLayer::Interfaz);
		bRendirse->addComponent<Transform2>(Vector2D(sdlutils().width() / 2 - 200, sdlutils().height() / 2 + 200), 400, 200);
		bRendirse->addComponent<Image>(&sdlutils().images().at("rendirse"));
		bRendirse->addComponent<ButtonSurrender>(pS);
	}
}

void SettingsState::goBack(GameStateMachine* gsm) {
	gsm->popState();
}

void SettingsState::tickVolume(bool state) {
	if (state) sdlutils().changeSFXvolume(0);
	else sdlutils().restoreAllVolume();
}

void SettingsState::update() {
	GameState::update();
	if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		gameStateMachine->popState();
	}
}


void SettingsState::goControles(GameStateMachine* gsm) {
	gsm->pushState(new ControlState(gsm, &sdlutils().images().at("controles"), false));
}