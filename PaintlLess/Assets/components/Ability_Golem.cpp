#include "Ability_Golem.h"

void Ability_Golem::init() {
    tr = entity_->getComponent<Transform>();
    assert(tr != nullptr);
    mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
    assert(mapa != nullptr);
}

void Ability_Golem::generateWall() {
    Vector2D pos = mapa->SDLPointToMapCoords(tr->getPos());

    auto* e = entity_->getMngr()->addEntity(RenderLayer::Tablero3);

    e->addComponent<Transform>(
        pos, //Posicion
        Vector2D(),     //Velocidad
        50.0f,          //Ancho
        50.0f,          //Alto
        0.0f);
    e->addComponent<Image>(&sdlutils().images().at("wall"));
    e->addComponent<Health>(2);
}