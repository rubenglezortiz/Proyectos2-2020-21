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

SettingsState::SettingsState(GameStateMachine* gsm, PlayState* pS) : GameState(gsm) {
	auto* fondo = mngr_->addEntity(RenderLayer::Fondo);
	fondo->addComponent<Transform2>(Vector2D(0, 0), sdlutils().width(), sdlutils().height());
	fondo->addComponent<Image>(&sdlutils().images().at("menuSP"));

	auto* barra = mngr_->addEntity(RenderLayer::Interfaz);
	barra->addComponent<Transform2>(Vector2D(sdlutils().width() / 2 - 450, sdlutils().height() - 150), 900, 100);
	barra->addComponent<Image>(&sdlutils().images().at("barraVolumen"));

	auto* volumen = mngr_->addEntity(RenderLayer::Interfaz);
	volumen->addComponent<Transform2>(Vector2D(sdlutils().volume() * 8 + (sdlutils().width() / 2 - 400), sdlutils().height() - 150), 100, 100);
	volumen->addComponent<Image>(&sdlutils().images().at("botonVolumen"));
	volumen->addComponent<ButtonVolume>();

	auto* botonX = mngr_->addEntity(RenderLayer::Interfaz);
	botonX->addComponent<Transform>(Vector2D(sdlutils().width() - 150, 150), 100, 100);
	botonX->addComponent<Image>(&sdlutils().images().at("botonAtras"));
	botonX->addComponent<MenuButton>(gsm, goBack);

	auto* botonTick = mngr_->addEntity(RenderLayer::Interfaz);
	botonTick->addComponent<Transform2>(Vector2D(sdlutils().width()/2, sdlutils().height()/2), 100, 100);
	botonTick->addComponent<Image>(&sdlutils().images().at("tick1"));
	botonTick->addComponent<ButtonTick>(&sdlutils().images().at("tick2"), tickVolume);

	if (pS != nullptr) {
		playState_ = pS;
		auto* bRendirse = mngr_->addEntity(RenderLayer::Interfaz);
		bRendirse->addComponent<Transform2>(Vector2D(sdlutils().width() / 2 - 150, sdlutils().height() / 2 + 150), 100, 100);
		bRendirse->addComponent<Image>(&sdlutils().images().at("barraVolumen"));
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
