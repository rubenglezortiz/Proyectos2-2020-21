#include "./Health.h"

void Health::init() {
	tr = entity_->getComponent<Transform>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	mapa->setCharacter(mapa->SDLPointToMapCoords(tr->getPos()), entity_); //Poner en la casilla la entidad
	//setLives();
}

void Health::hit() {
	lives--;
	if (lives == 0) {
		mapa->removeCharacter(mapa->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos())); //Quitar la entidad muerta
		if (entity_->getComponent<DejaMuro>() != nullptr) {    //Deja muro si es el golem
			entity_->getComponent<DejaMuro>()->generateWall();
		}
		entity_->setActive(false);
	}
	std::cout << "Ataca";
}

void Health::render() {
	SDL_Rect src;
	src.x = 0; src.y = 0; src.w = tex->width(); src.h = tex->height();

	Vector2D pos= tr->getPos();

	SDL_Rect dest;
	dest.x = pos.getX()+mapa->getCellWidth()- tr->getW()/6; dest.y = pos.getY()+mapa->getCellHeight()- tr->getH()/5;
	dest.w = tr->getW()/6; dest.h = tr->getH()/5;

	for (int i = 0; i < lives; ++i)
	{
		tex->render(src, dest, 0);
		//Cada vez que pinta uno cambia la posición x del siguiente
		dest.x = dest.x - dest.w;
	}
}

//void Health::setLives() {
//	for (int i = 0; i < lives; ++i) {
//		auto l = entity_->getMngr()->addEntity(RenderLayer::Interfaz);
//		Vector2D pos = Vector2D(1,/*piece->getPos().getX() + piece->getW() - 5 * i*/1);
//		l->addComponent<Transform>(pos, 50.0f, 500.0f);
//		/*l->getComponent<Transform>()->setH(25.0);
//		l->getComponent<Transform>()->setW(25.0);*/
//		l->addComponent<Image>(&sdlutils().images().at("life"));
//	}
//}