#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../game/GameStateMachine.h"
#include "Transform.h"
#include "Image.h"
#include "MenuButton.h"
#include "../utils/Collisions.h"

class ButtonSelected : public Component {

private:
	Transform* tr_;
	MenuButton* bt_;
	Texture* tex1_;
	Texture* tex2_;
	Image* img_;
	GameStateMachine* gsm_;
	int contador = 0;
	int max = 0;
	bool selected = false;
	const std::string SONIDO = "seleccionSound";

protected:
	CallBackOnClick* cbOnClick;

public:
	ButtonSelected(GameStateMachine* gsm, Texture* tex, CallBackOnClick* cb) : gsm_(gsm), cbOnClick(cb), tex1_(tex), tex2_(nullptr), tr_(nullptr), bt_(nullptr), img_(nullptr) {}
	virtual ~ButtonSelected() {}
	void init() override;
	void update() override;
};