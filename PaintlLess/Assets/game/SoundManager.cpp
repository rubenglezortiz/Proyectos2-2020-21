#include "SoundManager.h"
#include "../sdlutils/SDLUtils.h"

void SoundManager::changeSFXvolume(int volume) {
	// Habilidades.
	sdlutils().soundEffects().at("alquimistaSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("ataqueSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("bombaSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("caeraguaSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("click").setChunkVolume(volume);
	sdlutils().soundEffects().at("crearEnredaderasSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("enredaderasSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("kirinSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("loboSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("monaguilloSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("moveSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("muerteSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("vikingoSound").setChunkVolume(volume);

	// Botones.
	sdlutils().soundEffects().at("menuButtonSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("menuInicioSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("moveSound").setChunkVolume(volume);
	sdlutils().soundEffects().at("seleccionSound").setChunkVolume(volume);
}

void SoundManager::restoreAllVolume() {
	changeSFXvolume(59);
}