#include "Ability_Skeleton.h"

Ability_Skeleton::Ability_Skeleton(int lv) : livesSk_(lv) { }

void Ability_Skeleton::OnDie()
{
    if (livesSk_ > 4) {
        mapa_ = this->getAbility()->getMap();
        Entity* entity = this->getAbility()->getEntity();
        Transform* characterTr = entity->getComponent<Transform>();

        Vector2D pos = mapa_->SDLPointToMapCoords(characterTr->getPos());
        entity_ = entity->getMngr()->addEntity(RenderLayer::Tablero3);
        entity_->addComponent<Transform>(
            pos, //Posicion
            Vector2D(),     //Velocidad
            50.0f,          //Ancho
            50.0f,          //Alto
            0.0f);
        entity_->setGroup<Personajes>(entity_);

        FramedImage* fr;
        if (entity->hasGroup<Equipo_Azul>()) {
            entity_->setGroup<Equipo_Azul>(entity_);
            fr = entity_->addComponent<FramedImage>(&sdlutils().images().at("esqueletoSheetRD"), 150, Unit::Esqueleto, false, true);
        }
        else {
            entity_->setGroup<Equipo_Rojo>(entity_);
            fr = entity_->addComponent<FramedImage>(&sdlutils().images().at("esqueletoSheetAD"), 150, Unit::Esqueleto, false, true);
        }
        fr->setAnim(DeathA);
        entity_->addComponent<Attack>(mapa_->getPlayState(), 1, 1, 0);
        entity_->addComponent<Movimiento>(mapa_->getPlayState(), 1);
        entity_->addComponent<Health>(100);
        entity_->addComponent<Ability>(new Ability_Skeleton(2));
        mapa_->setCharacter(pos, entity_);
    }
}

void Ability_Skeleton::finTurno() {
     entity_ = this->getAbility()->getEntity();
     mapa_ = this->getAbility()->getMap();
     if (livesSk_ < 3) 
         livesSk_--;
     if (livesSk_ <= 0) {
         mapa_->removeCharacter(mapa_->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos())); //Quitar la entidad muerta	
         entity_->getComponent<FramedImage>()->setAnim(DeathA, true);
     }
}