#include "ButtonVolume.h"
#include "Transform.h"
#include "../sdlutils/InputHandler.h"

void ButtonVolume::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void ButtonVolume::update() {
	int mX = ih().getMousePos().first;
	int borde = sdlutils().width() / 2 - 400;
	// Si ha clicado el botón, lo selecciona o deja de seleccionar.
	if (mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && ih().getMouseButtonState(ih().LEFT))
		pulse_ = !pulse_;
	// Controla el volumen según la posición del ratón.
	if (pulse_) tr_->getPos().setX(mX - tr_->getW() / 2);
	// Deshabilita la selección del botón si se ha salido de los bordes.
	if (tr_->getPos().getX() < borde || tr_->getPos().getX() + tr_->getW() > borde + 850) pulse_ = false;
	// Gestiona el entero del volumen, asignándole un valor correspondiente a la posición del botón (simula el scroll lateral).
	volume_ = ((tr_->getPos().getX() - borde) / 8);
	// Si el botón está muy a la izquierda, directamente no hay volumen.
	if (tr_->getPos().getX() < borde + 100) volume_ = 0;
	// Cambia el volumen de los sonidos.
	sM_->changeSFXvolume(volume_);
}
	