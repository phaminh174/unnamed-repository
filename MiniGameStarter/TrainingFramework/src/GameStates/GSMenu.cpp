#include "GSMenu.h"
#include "Camera.h"
#include "cstdio"
#include "../Bird.h";
GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), 
	m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}


template <typename T> std::string tostr(const T& t)
{
	std::ostringstream os; os << t; return os.str();
}

Bird* birdMenu;

void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 + 200);
	button->SetSize(200, 200);
	button->SetOnClick([]() {
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);
	FILE* fp;
	char highscore[8];
	fp = fopen("../Data/highscore.txt", "r");
	fscanf(fp, "%s", highscore);
	fclose(fp);

	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("04B_19__.ttf");
	m_textGameName = std::make_shared< Text>(shader, font, "High Score: " + tostr(highscore), TextColor::WHITE, 3.0f);
	m_textGameName->Set2DPosition(Vector2(125, 450));

	birdMenu = new Bird();
	birdMenu->SetPosition(360, 310);
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
	FILE* fp;
	char highscore[8];
	fp = fopen("../Data/highscore.txt", "r");
	fscanf(fp, "%s", highscore);
	fclose(fp);


	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("04B_19__.ttf");
	m_textGameName = std::make_shared< Text>(shader, font, "High Score: " + tostr(highscore), TextColor::WHITE, 3.0f);
	m_textGameName->Set2DPosition(Vector2(125, 450));
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	birdMenu->Update(deltaTime);
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_background->Draw();
	birdMenu->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
}
