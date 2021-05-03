#pragma once

#include "../ecs/Component.h"
#include "../game/SoundManager.h"
class Transform;

class ButtonVolume : public Component {
private:
	bool pulse_ = false;
	int volume_ = 0;
	Transform* tr_;
	SoundManager* sM_;
public:
	ButtonVolume() { sM_ = new SoundManager(); }
	virtual ~ButtonVolume(){}
	void init() override;
	void update() override;
};