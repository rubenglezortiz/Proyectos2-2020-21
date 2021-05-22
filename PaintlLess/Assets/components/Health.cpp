#include "Health.h"
#include "../game/PlayState.h"

void Health::init() {
	tr = entity_->getComponent<Transform>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();

	//setLives();
}

void Health::hit(int damage) {
	lives -= damage;
	if (lives <= 0) {
		kill(mapa, entity_);
	}
	std::cout << "Ataca";
}

void Health::healMonaguillo(int healing) {
	if (lives != livesMax)
		lives += healing;
}

void Health::heal(int healing) {
	if (lives != livesMax - 1)
		lives += healing;
}

void Health::kill(GameMap* mapa, Entity* entity_)
{
	Vector2D tr = entity_->getComponent<Transform>()->getPos();
	mapa->removeCharacter(mapa->SDLPointToMapCoords(tr)); //Quitar la entidad muerta		
	mapa->removeObstaculo(mapa->SDLPointToMapCoords(tr));
	Color color;
	if (mapa->getPlayState()->getCurrentPlayer() == Segundo) color = Rojo;
	else color = Azul;
	mapa->setColor(mapa->SDLPointToMapCoords(tr), color);

	Ability* ability = entity_->getComponent<Ability>();
	if (ability != nullptr)
	{
		ability->OnDie();
	}

	//else {
	//	sdlutils().soundEffects().at("muerteSound").play(); //-----------------------------------------------------------	
	//}
	if (entity_->getComponent<FramedImage>() != nullptr)
		entity_->getComponent<FramedImage>()->setAnim(DeathA);
	else entity_->setActive(false); //ESTO HABRÍA QUE QUITARLO CUANDO SE METAN TODAS LAS ANIM		
}

void Health::render() {
	if (lives < 50) {
		if (entity_->hasGroup<Equipo_Rojo>())
		{
			SDL_Rect src;
			src.x = 0; src.y = 0; src.w = tex->width(); src.h = tex->height();

			Vector2D pos = tr->getPos();

			SDL_Rect dest;
			dest.x = pos.getX() + mapa->getCellWidth() - tr->getW() / 6; dest.y = pos.getY() + mapa->getCellHeight() - tr->getH() / 2;
			dest.w = tr->getW() / 6; dest.h = tr->getH() / 5;

			for (int i = 0; i < lives; ++i)
			{
				tex->render(src, dest, 0);
				//Cada vez que pinta uno cambia la posici�n x del siguiente
				dest.x = dest.x - dest.w;
			}
		}
		else
		{
			SDL_Rect src;
			src.x = 0; src.y = 0; src.w = tex->width(); src.h = tex->height();

			Vector2D pos = tr->getPos();

			SDL_Rect dest;
			dest.x = pos.getX() - mapa->getCellWidth() + tr->getW(); dest.y = pos.getY() + mapa->getCellHeight() - tr->getH() / 2;
			dest.w = tr->getW() / 6; dest.h = tr->getH() / 5;

			for (int i = 0; i < lives; ++i)
			{
				tex->render(src, dest, 0);
				//Cada vez que pinta uno cambia la posici�n x del siguiente
				dest.x = dest.x + dest.w;
			}
		}
	}
}

//void Health::setLives() {
//    for (int i = 0; i < lives; ++i) {
//        auto l = entity->getMngr()->addEntity(RenderLayer::Interfaz);
//        Vector2D pos = Vector2D(1,/*piece->getPos().getX() + piece->getW() - 5 * i/1);
//        l->addComponent<Transform>(pos, 50.0f, 500.0f);
//        /l->getComponent<Transform>()->setH(25.0);
//        l->getComponent<Transform>()->setW(25.0);*/
//        l->addComponent<Image>(&sdlutils().images().at("life"));
//    }
//}