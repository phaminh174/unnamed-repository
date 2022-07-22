#pragma once
#include "Sprite2D.h"
#include "SpriteAnimation.h"

class Pipe : public Sprite2D
{
public:
	Pipe();
	void Init() override;
	void Update(GLfloat deltatime) override;
	void Draw();
	void Moving(GLfloat deltatime);
	bool getStartFall();
	void setStartFall(bool i);
	Vector2 getUpperPipePos();
	Vector2 getLowerPipePos();
protected:
	std::shared_ptr<Model> model;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite2D> upperPipe;
	std::shared_ptr<Sprite2D> lowerPipe;
	float x;
	float y;
	float velocity = 350;
	int pos;
	bool startFall = false;
};

