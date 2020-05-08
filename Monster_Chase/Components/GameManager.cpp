#include "GameManager.h"
#include "Entity Component System/Game Scene/GameScene.h"
#include "DebugTools/ConsolePrint.h"
#include "Rendering/RenderingComponent/SpriteRenderer.h"
const std::string GameManager::tag = "gamecontroller";
GameManager::GameManager(const float& i_resetTime, const float& i_width)
{
	m_timeToReset = i_resetTime;
	m_screenWidth = i_width;
}

GameManager::~GameManager()
{
}

void GameManager::update(UpdateParams * params)
{
	if (!m_initialized)
	{
		if (onStart())
		{
			m_initialized = true;
			stopMatch();
		}
	
	}

	if (m_matchIsRunning)
	{
		if (m_isResetting)
		{
			m_resetTimer += (float)params->deltaTime;			
			
			if (m_resetTimer >= m_timeToReset)
			{
				m_resetTimer = 0;
				m_isResetting = false;
				bc->launch();
			}
		}

		if (ball->position.x < -m_screenWidth)
		{
			m_p2Score += 1;
			bc->reset();
			m_isResetting = true;
			DEBUG_PRINT("Point p2\n");
			DEBUG_PRINT("Resetting round p2\n");
		}
		else if (ball->position.x > m_screenWidth)
		{
			m_p1Score += 1;
			bc->reset();
			m_isResetting = true;
			DEBUG_PRINT("Point p1\n");
			DEBUG_PRINT("Resetting round p2\n");
		}

		updateScore();
	}
	else
	{
		InputManager::Key keyDown = InputManager::lastKeyDown;

		if (keyDown == InputManager::G)
		{
			startMatch();
		}
	}	

}

void GameManager::draw(UpdateParams * params)
{
}

void GameManager::onAddToObject()
{
}

void GameManager::Serialize(json & j)
{
	j["GameManager"] = { {"timeToReset",m_timeToReset},{"screenWidth",m_screenWidth} };
}

bool GameManager::onStart()
{
	DEBUG_PRINT("Initializing Game Manager\n");
	ball = gameObject->scene->getGameObjectByName("Ball");
	if (ball == nullptr)
	{
		DEBUG_PRINT("Initialization failed no ball found in scene\n");
		return false;
	}


	splash = gameObject->scene->CreateGameObject();

	p1Help = gameObject->scene->CreateGameObject();
	p2Help = gameObject->scene->CreateGameObject();



	splash->addComponent(new SpriteRenderer("data\\splash.dds"));
	p1Help->addComponent(new SpriteRenderer("data\\p1help.dds"));
	p2Help->addComponent(new SpriteRenderer("data\\p2help.dds"));

	p1Help->position = Vector2(-200, -300);
	p2Help->position = Vector2(200, -300);

	bc = dynamic_cast<BallController*>(ball->getComponent(BallController::tag).getRawPointer());	
	Vector2 p1Pos(-300, 200);
	Vector2 p2Pos(300, 200);
	for (int i = 0; i < 5; i++)
	{
		p1[i] = gameObject->scene->CreateGameObject();
		p2[i] = gameObject->scene->CreateGameObject();

		if (i == 0)
		{
			p1[i]->addComponent(new SpriteRenderer("data\\0.dds"));
			p1[i]->position = p1Pos;
			p1[i]->enabled = false;
			p2[i]->addComponent(new SpriteRenderer("data\\0.dds"));
			p2[i]->position = p2Pos;
			p2[i]->enabled = false;
		}
		else if(i==1)
		{
			p1[i]->addComponent(new SpriteRenderer("data\\1.dds"));
			p1[i]->position = p1Pos;
			p1[i]->enabled = false;
			p2[i]->addComponent(new SpriteRenderer("data\\1.dds"));
			p2[i]->position = p2Pos;
			p2[i]->enabled = false;
		}
		else if (i == 2)
		{
			p1[i]->addComponent(new SpriteRenderer("data\\2.dds"));
			p1[i]->position = p1Pos;
			p1[i]->enabled = false;
			p2[i]->addComponent(new SpriteRenderer("data\\2.dds"));
			p2[i]->position = p2Pos;
			p2[i]->enabled = false;
		}
		else if (i == 3)
		{
			p1[i]->addComponent(new SpriteRenderer("data\\3.dds"));
			p1[i]->position = p1Pos;
			p1[i]->enabled = false;
			p2[i]->addComponent(new SpriteRenderer("data\\3.dds"));
			p2[i]->position = p2Pos;
			p2[i]->enabled = false;
		}
		else if (i == 4)
		{
			p1[i]->addComponent(new SpriteRenderer("data\\p1win.dds"));
			p1[i]->position = p1Pos;
			p1[i]->enabled = false;
			p2[i]->addComponent(new SpriteRenderer("data\\p2win.dds"));
			p2[i]->position = p2Pos;
			p2[i]->enabled = false;
		}
	}
	
	return true;
}

void GameManager::updateScore()
{
	for (int i = 0; i < 5; i++)
	{
		p1[i]->enabled = false;
		p2[i]->enabled = false;
	}
	if (m_p1Score >= 4)
	{
		p1[4]->enabled = true;
		stopMatch();
	}
	else if (m_p2Score >= 4)
	{
		p2[4]->enabled = true;
		stopMatch();
	}
	else
	{
		p1[m_p1Score]->enabled = true;
		p2[m_p2Score]->enabled = true;
	}
}

void GameManager::stopMatch()
{

	m_isResetting = false;
	m_matchIsRunning = false;
	splash->enabled = true;	
	p1Help->enabled = true;
	p2Help->enabled = true;
	DEBUG_PRINT("Ending Match\n");
}

void GameManager::startMatch()
{
	m_isResetting = true;
	m_matchIsRunning = true;
	splash->enabled = false;
	m_p1Score = 0;
	m_p2Score = 0;
	p1Help->enabled = false;
	p2Help->enabled = false;
	DEBUG_PRINT("Starting Match\n");
}
