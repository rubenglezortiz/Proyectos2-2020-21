#include "ButtonVolume.h"
#include "Transform2.h"
#include "../sdlutils/InputHandler.h"

void ButtonVolume::init() {
	tr_ = entity_->getComponent<Transform2>();
	assert(tr_ != nullptr);
}

void ButtonVolume::update() {
	int borde = 230;

	int volumen = 0;
	if (music) volumen = sdlutils().volumeMUS();
	else volumen = sdlutils().volumeSFX();

	tr_->getPos().setX(volumen * 9 + borde);

	int mX = ih().getMousePos().first;
	// Si ha clicado el botón, lo selecciona o deja de seleccionar.
	if (mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && ih().getMouseButtonState(ih().LEFT))
		pulse_ = !pulse_;
	// Controla el volumen según la posición del ratón.
	if (pulse_) 
		tr_->getPos().setX(mX - tr_->getW() / 2);
	// Deshabilita la selección del botón si se ha salido de los bordes.
	if (tr_->getPos().getX() < borde || tr_->getPos().getX() + tr_->getW() > borde + 870) 
		pulse_ = false;
	// Gestiona el entero del volumen, asignándole un valor correspondiente a la posición del botón (simula el scroll lateral).
	volumen = ((tr_->getPos().getX() - borde) / 9);
	// Si el botón está muy a la izquierda, directamente no hay volumen.
	if (tr_->getPos().getX() < borde + 100) 
		volumen = 0;
	// Cambia el volumen de los sonidos.
	if (music)
		sdlutils().changeMusicVolume(volumen);
	else 
		sdlutils().changeSFXvolume(volumen);
}
	