#include "Ability_Golem.h"


void Ability_Golem::generateWall() {
    Vector2D pos = map->SDLPointToMapCoords(characterTr->getPos());
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