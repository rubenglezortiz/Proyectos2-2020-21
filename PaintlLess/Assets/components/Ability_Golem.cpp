#include "Ability_Golem.h"


void AbilityGolem (AbilityStruct* info) {
    GameMap* map = info->getAbility()->getMap();
    Entity* entity_ = info->getAbility()->getEntity();
    Transform* characterTr = entity_->getComponent<Transform>();

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
	map->setCharacter(pos, e);
}

Ability_Golem::Ability_Golem()
{
    setOnDie([](AbilityStruct* info) {AbilityGolem(info); });
}
