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
	this->Set2DPosition(240, 400);
	obj->SetSize(80, 57.6);
	this->SetSize(50, 50);
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
	// gravity
	obj = m_listAnimation.back();
	Vector3 objPos = obj->GetPosition();
	velocity += deltatime * 1000 * 4;
	objPos.y += velocity * deltatime;
	obj->Set2DPosition(objPos.x, objPos.y);

	//rotation
	Vector3 objRot = obj->GetRotation();
	velocityRot += deltatime * 12;
	objRot.z += velocityRot * deltatime; 
	if (objRot.z > PI / 4) objRot.z = PI / 4;
	obj->SetRotation(objRot);
}

bool Bird::getStartFall() {
	return startFall;
}

void Bird::setStartFall(bool i) {
	this->startFall = i;
}

void Bird::flap(float v) {
	this->velocity = v;
	Vector3 objRot = obj->GetRotation();
	if (objRot.z > 0) {
		this->velocityRot = -3*PI / 4 - (objRot.z);
	}
	else this->velocityRot = -PI / 2;
}

bool Bird::isCollided(Vector2 objPos , Vector2 objSize) {
	Vector2 pos = this->Get2DPosition();
	Vector2 size = this->GetSize();

	//Vector2 birdPos = Vector2(pos.x-size.x , pos.y - size.y);
	Vector2 birdPos = this->Get2DPosition();
	Vector2 birdSize = this->GetSize();
	
	float distX = (birdPos.x + (birdSize.x / 2)) - (objPos.x + (objSize.x) / 2);
	if (distX < 0)
		distX = -distX;

	float distW = (birdSize.x + objSize.x) / 2;

	float distY = (birdPos.y + (birdSize.y / 2)) - (objPos.y + (objSize.y) / 2);
	if (distY < 0)
		distY = -distY;

	float distH = (birdSize.y + objSize.y) / 2;

	return (distX <= distW && distY <= distH);
	return false;
}

void Bird::Up(GLfloat deltatime) {
	Vector2 pos = obj->Get2DPosition();
	pos.y -= 100 * deltatime;
	obj->Set2DPosition(pos.x,pos.y);
}

void Bird::Down(GLfloat deltatime) {
	Vector2 pos = obj->Get2DPosition();
	pos.y += 100 * deltatime;
	obj->Set2DPosition(pos.x, pos.y);
}

void Bird::Left(GLfloat deltatime) {
	Vector2 pos = obj->Get2DPosition();
	pos.x += 100 * deltatime;
	obj->Set2DPosition(pos.x, pos.y);
}

void Bird::Right(GLfloat deltatime) {
	Vector2 pos = obj->Get2DPosition();
	pos.x -= 100 * deltatime;
	obj->Set2DPosition(pos.x, pos.y);
}