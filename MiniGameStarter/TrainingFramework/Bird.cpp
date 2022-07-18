#include "Bird.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Sprite2D.h"
#include "..\GameManager\ResourceManagers.h"
void Bird::Update(GLfloat deltatime) {
	for (auto it : m_listAnimation)
	{
		it->Update(deltatime);
	}

	if (startFall)
	{
		this->falling(deltatime);
	}
}


void Bird::Init() {
}

Bird::Bird() 
{
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("flappy-bird.tga");
	obj = std::make_shared<SpriteAnimation>(model, shader, texture, 3, 1, 0, 0.1f);
	obj->Set2DPosition(240, 400);
	obj->SetSize(90, 125);
	m_listAnimation.push_back(obj);
	startFall = false;
}

Bird::~Bird() {

}
void Bird::Draw()
{
	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
}

void Bird::falling(GLfloat deltatime) {
	obj = m_listAnimation.back();
	Vector3 objPos = obj->GetPosition();
	velocity += deltatime * 1000 * 2;
	objPos.y += velocity * deltatime;
	obj->Set2DPosition(objPos.x, objPos.y);
}

bool Bird::getStartFall() {
	return startFall;
}

void Bird::setStartFall(bool i) {
	this->startFall = i;
}

void Bird::flap(float v) {
	this->velocity = v;
}
