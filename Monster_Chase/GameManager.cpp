#include "GameManager.h"
#include "GameScene.h"
#include "ConsolePrint.h"
#include "SpriteRenderer.h"
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
		onStart();
		m_initialized = true;
		stopRound();
	}

	if (m_roundIsRunning)
	{
		if (m_isResetting)
		{
			m_resetTimer += (float)params->deltaTime;
			float timeLeft = m_timeToReset - m_resetTimer;
			DEBUG_PRINT("Resetting ball in: %f\n", timeLeft);
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
		}
		else if (ball->position.x > m_screenWidth)
		{
			m_p1Score += 1;
			bc->reset();
			m_isResetting = true;
		}

		updateScore();
	}
	else
	{
		InputManager::Key keyDown = InputManager::lastKeyDown;

		if (keyDown == InputManager::G)
		{
			startRound();
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
}

void GameManager::onStart()
{
	DEBUG_PRINT("Initializing Game Manager");
	ball = gameObject->scene->getGameObjectByName("Ball");
	splash = gameObject->scene->CreateGameObject();
	splash->addComponent(new SpriteRenderer("data\\splash.dds"));

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
		stopRound();
	}
	else if (m_p2Score >= 4)
	{
		p2[4]->enabled = true;
		stopRound();
	}
	else
	{
		p1[m_p1Score]->enabled = true;
		p2[m_p2Score]->enabled = true;
	}
}

void GameManager::stopRound()
{
	m_isResetting = false;
	m_roundIsRunning = false;
	splash->enabled = true;	
}

void GameManager::startRound()
{
	m_isResetting = true;
	m_roundIsRunning = true;
	splash->enabled = false;
	m_p1Score = 0;
	m_p2Score = 0;
}
