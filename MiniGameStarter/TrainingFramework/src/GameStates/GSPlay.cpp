#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"



GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth+50, Globals::screenHeight+50);
	
	// foreground
	texture = ResourceManagers::GetInstance()->GetTexture("foreground.tga");
	m_foreground = std::make_shared<Sprite2D>(model, shader, texture);
	m_foreground->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight-50);
	m_foreground->SetSize(169*3, 57*3);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
			GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("04B_19__.ttf");
	m_score = std::make_shared< Text>(shader, font, "10", TextColor::WHITE, 2.0);
	m_score->Set2DPosition((float)Globals::screenWidth / 2-10, 60);

	// bird
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("flappy-bird.tga");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 3, 1, 0, 0.1f);
	
	obj->Set2DPosition(240, 400);
	obj->SetSize(90, 125);
	m_listAnimation.push_back(obj);
	m_KeyPress = 0;
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress |= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress |= 1<<1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress |= 1<<2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress |= 1<<3;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress ^= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	printf("mouse position: %d %d \n", x , y);
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

float gravity;
float velocity = 0;

void GSPlay::Update(float deltaTime)
{
	std::shared_ptr<SpriteAnimation> obj;
	obj = m_listAnimation.back();
	Vector3 objPos = obj->GetPosition();
	// gravity
	velocity += deltaTime * 1000 * 2;
	objPos.y += velocity * deltaTime;
	obj->Set2DPosition(objPos.x, objPos.y);
	switch (m_KeyPress)//Handle Key event
	{
	//case 1:
	//	// left
	//	objPos.x -= velocity * deltaTime;
	//	obj->Set2DPosition(objPos.x , objPos.y);
	//	break;
	//case 2:
	//	// down
	//	objPos.y += velocity * deltaTime;
	//	obj->Set2DPosition(objPos.x, objPos.y);
	//	break;
	//case 4:
	//	// right
	//	objPos.x += velocity * deltaTime;
	//	obj->Set2DPosition(objPos.x, objPos.y);
	//	break;
	case 8:
		// up
		velocity = -450;
		break;
	default:
		break;
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
	m_foreground->Draw();
}