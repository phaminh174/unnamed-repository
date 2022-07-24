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

using namespace std;

template <typename T> std::string tostr(const T& t)
{
	std::ostringstream os; os << t; return os.str();
}

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
float timer = 0;
bool gameOver;
int score;
bool playsound;


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth+50, Globals::screenHeight+50);
	
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
	m_panel1 = std::make_shared< Text>(shader, font, "YOU LOSE", TextColor::WHITE, 2.0);
	m_panel2 = std::make_shared< Text>(shader, font, "PLAY AGAIN?", TextColor::WHITE, 2.0);
	m_score = std::make_shared< Text>(shader, font, "Score: 0", TextColor::WHITE, 2.0);
	m_score->Set2DPosition((float)Globals::screenWidth / 2 - 100, 60);
	m_panel1->Set2DPosition((float)Globals::screenWidth / 2 - 100, (float)Globals::screenHeight / 2 - 100);
	m_panel2->Set2DPosition((float)Globals::screenWidth / 2 - 125, (float)Globals::screenHeight / 2 );

	//foreground
	foreground = new Foreground();

	//bird
	bird = new Bird();

	//pipe
	pipe1 = new Pipe();
	pipe2 = new Pipe();

	timer = 0;
	m_KeyPress = 0;
	score = 0;
	gameOver = false;
	playsound = false;
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


void GSPlay::Update(float deltaTime)
{
	if (gameOver) {
		bird->setGameOver(true);
		pipe1->setGameOver(true);
		pipe2->setGameOver(true);
		foreground->setGameOver(true);
		if (!playsound) {
			ResourceManagers::GetInstance()->PlaySound("sfx_hit.wav");
			playsound = true;
		}
	}
	// check va cham
	if (bird->Get2DPosition().y < 0) gameOver = true;
	if (bird->isCollided(pipe1->getLowerPipePos(), pipe1->GetSize())) {
		gameOver = true;
	}
	if (bird->isCollided(pipe1->getUpperPipePos(), pipe1->GetSize())) {
		gameOver = true;
	}

	if (bird->isCollided(pipe2->getLowerPipePos(), pipe2->GetSize())) {
		gameOver = true;
	}
	if (bird->isCollided(pipe2->getUpperPipePos(), pipe2->GetSize())) {
		gameOver = true;
	}

	if (bird->isCollided(foreground->getFirstForeground(), foreground->GetSize()) || bird->isCollided(foreground->getSecondForeground(), foreground->GetSize()))
	{
		gameOver = true;
	}

	// diem
	if (!gameOver)
	{
		if (pipe1->Scored(bird->Get2DPosition(), bird->GetSize()) || pipe2->Scored(bird->Get2DPosition(), bird->GetSize())) {
			score++;
			m_score->SetText("Score: " + tostr(score));
		}
	}
	if (bird->getStartFall())
	{
		timer += deltaTime;
		if (timer > 1.2) {
			pipe2->setStartFall(true);
			timer = 0;
		}
	}
	foreground->Update(deltaTime);
	pipe1->Update(deltaTime);
	pipe2->Update(deltaTime);
	bird->Update(deltaTime);
	switch (m_KeyPress)//Handle Key event
	{
	case 1:
		//bird->Right(deltaTime , 500);
		break;
	case 2:
		//bird->Down(deltaTime, 500);
		break;
	case 4:
		//bird->Left(deltaTime, 500);
		break;
	case 8:
		// up
		bird->setStartFall(true);
		pipe1->setStartFall(true);
		bird->flap(-600);
		break;
	default:
		break;
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	bird->Draw();
	pipe1->Draw();
	pipe2->Draw();
	foreground->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_score->Draw();
	if (gameOver) {
		m_panel1->Draw();
		m_panel2->Draw();
	}
}

