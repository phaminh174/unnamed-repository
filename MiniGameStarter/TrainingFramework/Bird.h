#pragma once
#include "Sprite2D.h"
#include "ResourceManagers.h"

class Bird : public Sprite2D
{
public:
	Bird() {
		//texture = ResourceManagers->GetTexture();
		y = 400;
	}
	void draw() {

	}
	void update(float delta) {
		vel += delta * 20;
		y += vel * delta;
	}
private:
	ResourceManagers ResourceManagers;
	float y;
	float vel;
};

