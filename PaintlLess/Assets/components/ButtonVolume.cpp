#include "ButtonVolume.h"
#include "Transform2.h"
#include "../sdlutils/InputHandler.h"

void ButtonVolume::init() {
	tr_ = entity_->getComponent<Transform2>();
	assert(tr_ != nullptr);
	volume_ = tr_->getPos().getX() * 8;
}

void ButtonVolume::update() {
	volume_ = sdlutils().volume();
	tr_->getPos().setX(sdlutils().volume() * 8 + (sdlutils().width() / 2 - 400));
	int mX = ih().getMousePos().first;
	int borde = sdlutils().width() / 2 - 400;
	// Si ha clicado el bot�n, lo selecciona o deja de seleccionar.
	if (mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && ih().getMouseButtonState(ih().LEFT))
		pulse_ = !pulse_;
	// Controla el volumen seg�n la posici�n del rat�n.
	if (pulse_) tr_->getPos().setX(mX - tr_->getW() / 2);
	// Deshabilita la selecci�n del bot�n si se ha salido de los bordes.
	if (tr_->getPos().getX() < borde || tr_->getPos().getX() + tr_->getW() > borde + 850) pulse_ = false;
	// Gestiona el entero del volumen, asign�ndole un valor correspondiente a la posici�n del bot�n (simula el scroll lateral).
	volume_ = ((tr_->getPos().getX() - borde) / 8);
	// Si el bot�n est� muy a la izquierda, directamente no hay volumen.
	if (tr_->getPos().getX() < borde + 100) volume_ = 0;
	// Cambia el volumen de los sonidos.
	sdlutils().changeSFXvolume(volume_);
}
	