#pragma once
#include "SpriteAnimation.h"

class Bird : public SpriteAnimation
{
public:
	void Init() override;
	void Update(GLfloat deltatime) override;
	//bool isCollider
protected:
	float x;
	float y;
	float vel;
};

