#include "Bird.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Sprite2D.h"

void Bird::Update(GLfloat deltatime) {
	vel += deltatime * 20;
	y += vel * deltatime;
	this->Set2DPosition(x, y);
}

void Bird::Init() {
	this->Set2DPosition(x, y);
}