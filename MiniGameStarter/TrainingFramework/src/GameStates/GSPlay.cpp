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
#include "../Bird.h";
#include "../Pipe.h";
#include "../Foreground.h";



GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}

Bird* bird;
Pipe* pipe1;
Pipe* pipe2;
Foreground* foreground;

void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth+50, Globals::screenHeight+50);
	
	//// foreground
	//texture = ResourceManagers::GetInstance()->GetTexture("foreground.tga");
	//m_foreground = std::make_shared<Sprite2D>(model, shader, texture);
	//m_foreground->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight+20);
	//m_foreground->SetSize(169*5, 57*3);

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

	//foreground
	foreground = new Foreground();

	//bird
	bird = new Bird();

	//pipe
	pipe1 = new Pipe();
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
float timer = 0;

void GSPlay::Update(float deltaTime)
{
	if (bird->getStartFall())
	{
		timer += deltaTime;
		if (timer > 1.2 && pipe2 == NULL) {
			pipe2 = new Pipe();
			pipe2->setStartFall(true);
			timer = 0;
		}
	}
	foreground->Update(deltaTime);
	pipe1->Update(deltaTime);
	if (pipe2 != NULL)
	pipe2->Update(deltaTime);
	// gravity
	bird->Update(deltaTime);
		Vector2 birdsize = bird->GetSize();
	switch (m_KeyPress)//Handle Key event
	{
	case 8:
		// up
		printf("%f %f \n", birdsize.x, birdsize.y);
		if (!bird->getStartFall()) {
			bird->setStartFall(true);
			pipe1->setStartFall(true);
		}
		bird->flap(-450);
		break;
	default:
		break;
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	/*for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}*/

}

void GSPlay::Draw()
{
	m_background->Draw();
	bird->Draw();
	pipe1->Draw();
	if (pipe2 != NULL)
	pipe2->Draw();
	foreground->Draw();
	//m_foreground->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_score->Draw();
}