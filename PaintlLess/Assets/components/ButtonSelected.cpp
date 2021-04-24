#include "ButtonSelected.h"

void ButtonSelected::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	bt_ = entity_->getComponent<MenuButton>();
	assert(bt_ != nullptr);
	img_ = entity_->getComponent<Image>();
	assert(img_ != nullptr);
	tex2_ = img_->getTexture();
	max = bt_->getGSM()->getCharSel()->getMax();
}

void ButtonSelected::update() {
	cont = bt_->getGSM()->getCharSel()->getCont();
	if (selection() && bt_->select()) {
		img_->setTexture(tex_);
		selected = true;
	}
	else if (!bt_->select()) {
		img_->setTexture(tex2_);
		selected = false;
	}
}

bool ButtonSelected::selection() {
	if (cont < max && !selected) return true;
	else return false;
}