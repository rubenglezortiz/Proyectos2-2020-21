#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../game/GameStateMachine.h"
#include "Transform.h"
#include "Image.h"
#include "MenuButton.h"

class ButtonSelected : public Component {

private:
	Transform* tr_;
	MenuButton* bt_;
	Texture* tex_;
	Texture* tex2_;
	Image* img_;
	SDL_Rect dest;
	int cont; 
	int max;
	bool selected = false;
public:
	ButtonSelected(Texture* tex) : tex_(tex), tr_(nullptr), bt_(nullptr) {
	}

	virtual ~ButtonSelected(){}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
		bt_ = entity_->getComponent<MenuButton>();
		assert(bt_ != nullptr);
		img_ = entity_->getComponent<Image>();
		assert(img_ != nullptr);
		tex2_ = img_->getTexture();
		max = bt_->getGSM()->getCharSel()->getMax();
		dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
	}

	void update() override {
		cont = bt_->getGSM()->getCharSel()->getCont();
		if (selection() && bt_->select()){
			img_->setTexture(tex_);
			selected = true;
		}
		else if (!bt_->select()) {
			img_->setTexture(tex2_);
			selected = false;
		}
	}

	bool selection() {
		if (cont < max && !selected) return true;
		else return false;
	}

};