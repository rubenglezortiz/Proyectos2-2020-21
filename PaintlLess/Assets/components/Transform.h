// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../GameMap.h"


class Transform : public Component {
public:
	Transform() :
		pos_(), vel_(), width_(), height_(), rotation_(), mapa(nullptr), foo_(false) {
	}

	Transform(Vector2D pos, float width, float height) :
		pos_(pos),
		width_(width),
		height_(height),
		vel_(Vector2D()),
		rotation_(0.0),
		mapa(nullptr) 
	{
	}
	Transform(Vector2D pos, Vector2D vel, float width, float height,
		float rotation, bool foo = false) :
		pos_(pos), //
		vel_(vel), //
		width_(width), //
		height_(height), //
		rotation_(rotation),
		mapa(nullptr),
		foo_(foo)
	{
	}

	virtual ~Transform() {
	}

	Vector2D& getPos() {
		return pos_;
	}

	Vector2D& getVel() {
		return vel_;
	}

	float getH() const {
		return height_;
	}

	void setH(float height) {
		height_ = height;
	}

	float getW() const {
		return width_;
	}

	void setW(float width) {
		width_ = width;
	}

	float getRot() const {
		return rotation_;
	}

	void setRot(float rot) {
		rotation_ = rot;
	}

	void update() override {
	}


	void init() override;

private:
	
	Entity* mapa;
	Vector2D pos_;
	Vector2D vel_;
	float width_;
	float height_;
	float rotation_;
	bool foo_;
};

