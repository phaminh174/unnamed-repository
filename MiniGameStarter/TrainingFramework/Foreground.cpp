#include "Foreground.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Sprite2D.h"
#include "..\GameManager\ResourceManagers.h"
void Foreground::Update(GLfloat deltatime) {
	foreground1->Update(deltatime);
	foreground2->Update(deltatime);
	Moving(deltatime);
}


void Foreground::Init() {
}

Foreground::Foreground()
{
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("foreground.tga");
	foreground1 = std::make_shared<Sprite2D>(model, shader, texture);
	foreground2 = std::make_shared<Sprite2D>(model, shader, texture);
	foreground1->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight + 20);
	foreground1->SetSize(169 * 5, 57 * 3);
	foreground2->Set2DPosition(3*(float)Globals::screenWidth / 2, (float)Globals::screenHeight + 20);
	foreground2->SetSize(169 * 5, 57 * 3);
	this->SetSize(169 * 5, 57 * 3);
}


void Foreground::Draw()
{
	foreground1->Draw();
	foreground2->Draw();
}

void Foreground::Moving(GLfloat deltatime) {
	Vector2 pos = foreground1->Get2DPosition();
	pos.x -= velocity * deltatime;
	if (pos.x < -(float)Globals::screenWidth / 2) {
		pos.x = 3 * (float)Globals::screenWidth / 2;
	}
	foreground1->Set2DPosition(pos.x, pos.y);

	pos = foreground2->Get2DPosition();
	pos.x -= velocity * deltatime;
	if (pos.x < -(float)Globals::screenWidth / 2) {
		pos.x = 3 * (float)Globals::screenWidth / 2;
	}
	foreground2->Set2DPosition(pos.x, pos.y);
}
