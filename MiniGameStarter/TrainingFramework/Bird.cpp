#include "Bird.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Sprite2D.h"
#include "..\GameManager\ResourceManagers.h"
void Bird::Update(GLfloat deltatime) {
	vel += deltatime * 20;
	y += vel * deltatime;
	this->Set2DPosition(x, y);
}

void Bird::Init() {
}

Bird::Bird() 
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("flappy-bird.tga");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 3, 1, 0, 0.1f);
	obj->Set2DPosition(240, 400);
	obj->SetSize(90, 125);
	Init();
}