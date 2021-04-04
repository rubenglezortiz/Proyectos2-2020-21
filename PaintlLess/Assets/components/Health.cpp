#include "./Health.h"

void Health::init() {
	auto mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	setLives();
}

void Health::hit() {
	lives--;
	if (lives == 0) {

		mapa->removeCharacter(mapa->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos()));
		entity_->setActive(false);
	}
}

void Health::setLives() {
	for (int i = 0; i < lives; ++i) {
		auto l = entity_->getMngr()->addEntity();
		Vector2D pos = Vector2D(1,/*piece->getPos().getX() + piece->getW() - 5 * i*/1);
		l->addComponent<Transform>(pos, 50.0f, 500.0f);
		l->getComponent<Transform>()->setH(25.0);
		l->getComponent<Transform>()->setW(25.0);
		l->addComponent<Image>(&sdlutils().images().at("life"));

	}
}