#include "Ability_Architect.h"
#include "../game/OffsetInfo.h"

void Ability_Architect::AbilityExecute(int x, int y) {
	// x e y
	//Crea imagen
	Entity* e = entity_->getMngr()->addEntity(RenderLayer::Tablero3);

	e->addComponent<Transform>(
		Vector2D(x, y), //Posicion
		Vector2D(),     //Velocidad
		50.0f,          //Ancho
		50.0f,          //Alto
		0.0f);

	e->addComponent<Image>(&sdlutils().images().at("wall"));
	e->addComponent<Health>(2);
	map->setObstaculo(Vector2D(x, y), e);
}