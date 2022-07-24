#include "Pipe.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Sprite2D.h"
#include "..\GameManager\ResourceManagers.h"



void Pipe::Update(GLfloat deltatime) {
	lowerPipe->Update(deltatime);
	upperPipe->Update(deltatime);
	if (startFall) this->Moving(deltatime);
}


void Pipe::Init() {
}

Pipe::Pipe()
{
	startFall = false;
	scored = false;
	gameOver = false;	
	pos = rand() % (Globals::screenHeight / 2 - 200 - (-Globals::screenWidth / 2 + 100) + 1) + (-Globals::screenWidth / 2 + 100);
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("LowerPipe.tga");
	lowerPipe = std::make_shared<Sprite2D>(model, shader, texture);
	texture = ResourceManagers::GetInstance()->GetTexture("UpperPipe.tga");
	upperPipe = std::make_shared<Sprite2D>(model, shader, texture);
	lowerPipe->Set2DPosition((float)Globals::screenWidth + 50, (float)Globals::screenHeight);
	lowerPipe->SetSize(100, 614);
	upperPipe->Set2DPosition((float)Globals::screenWidth + 50, 0);
	upperPipe->SetSize(100, 614);
	this->SetSize(95, 610);
	this->Set2DPosition(upperPipe->GetPosition().x, (upperPipe->GetPosition().y + lowerPipe->GetPosition().y) / 2);
}

void Pipe::Draw()
{
	lowerPipe->Draw();
	upperPipe->Draw();
}

void Pipe::Moving(GLfloat deltatime) {
	Vector3 upperPipePos = upperPipe->GetPosition();
	if (upperPipePos.x < -40) {
		upperPipePos.x = (float)Globals::screenWidth + 50;
		pos = rand() % (Globals::screenHeight/2-200 - (-Globals::screenWidth/2+100) + 1) + (-Globals::screenWidth/2+100);
		scored = false;	
	}
	upperPipePos.x -= velocity * deltatime;
	upperPipe->Set2DPosition(upperPipePos.x, pos);
	
	Vector3 lowerPipePos = lowerPipe->GetPosition();
	if (lowerPipePos.x < -40) {
		lowerPipePos.x = (float)Globals::screenWidth + 50;
		scored = false;	
	}
	lowerPipePos.x -= velocity * deltatime;
	lowerPipe->Set2DPosition(lowerPipePos.x, pos + (float)Globals::screenHeight);
}

bool Pipe::getStartFall() {
	return startFall;
}

void Pipe::setStartFall(bool i) {
	this->startFall = i;
}

Vector2 Pipe::getUpperPipePos() {
	return Vector2(upperPipe->GetPosition().x - this->m_iWidth/2, upperPipe->GetPosition().y - this->m_iHeight/2);
}

Vector2 Pipe::getLowerPipePos() {
	return Vector2(lowerPipe->GetPosition().x - this->m_iWidth/2, lowerPipe ->GetPosition().y - this->m_iHeight/2);
}

bool Pipe::Scored(Vector2 pos , Vector2 size) {
	if (pos.x + 160 >= (lowerPipe->Get2DPosition().x)  && !scored) {
		scored = true;
		ResourceManagers::GetInstance()->PlaySound("sfx_point.wav");
		return true;
	} 
	return false;
}

void Pipe::setGameOver(bool i) {
	gameOver = i;
	this->setStartFall(false);
}
