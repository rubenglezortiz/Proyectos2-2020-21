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
	int cont, max;
	bool selected = false;
public:
	ButtonSelected(Texture* tex) : tex_(tex), tr_(nullptr), bt_(nullptr) {}
	virtual ~ButtonSelected(){}
	void init() override;
	void update() override;
	bool selection();
};