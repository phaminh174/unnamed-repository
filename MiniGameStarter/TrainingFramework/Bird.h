#pragma once
#include "Sprite2D.h"
#include "SpriteAnimation.h"

class Bird : public Sprite2D
{
public:
	Bird();
	~Bird();
	void Init() override;
	void Update(GLfloat deltatime) override;
	void Draw();
	void falling(GLfloat deltatime);
	bool getStartFall();
	void setStartFall(bool i);
	void flap(float v);
	bool isCollided(Vector2 pos, Vector2 size);
	void Up(GLfloat deltatime, float v);
	void Down(GLfloat deltatime, float v);
	void Left(GLfloat deltatime, float v);
	void Right(GLfloat deltatime, float v);
	void setGameOver(bool i);
	Vector3 GetPosition();
	void	SetPosition(GLfloat x, GLfloat y);
protected:
	std::shared_ptr<Model> model;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<SpriteAnimation> obj;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	float x;
	float y;
	float velocity = 0;
	float velocityRot = 0;
	bool startFall;
	bool gameOver;
};

