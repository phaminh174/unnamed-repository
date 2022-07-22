#pragma once
#include "Sprite2D.h"
class Foreground : public Sprite2D
{
public:
	Foreground();
	void Init() override;
	void Update(GLfloat deltatime) override;
	void Draw();
	void Moving(GLfloat deltatime);
	Vector2 getFirstForeground();
	Vector2 getSecondForeground();
protected:
	std::shared_ptr<Model> model;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite2D> foreground1;
	std::shared_ptr<Sprite2D> foreground2;
	float x;
	float y;
	float velocity = 500;
};

