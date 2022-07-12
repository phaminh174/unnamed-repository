#pragma once
#include "Sprite2D.h"
class Bird : public Sprite2D
{
public:
	Bird() {
		y = 400;
	}
	void draw() {

	}
	void update(float delta) {
		vel += delta * 20;
		y += vel * delta;
	}
private:
	float y;
	float vel;
};

