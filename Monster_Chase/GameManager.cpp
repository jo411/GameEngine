#include "GameManager.h"
#include "GameScene.h"
#include "ConsolePrint.h"
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
	if (!initialized)
	{
		onStart();
		initialized = true;
	}
	if (m_isResetting)
	{
		m_resetTimer += (float)params->deltaTime;
		float timeLeft = m_timeToReset - m_resetTimer;
		DEBUG_PRINT("Resetting ball in: %f\n",timeLeft);
		if (m_resetTimer >= m_timeToReset)
		{
			m_resetTimer = 0;
			m_isResetting = false;	
			bc->launch();			
		}
	}

	if (ball->position.x<-m_screenWidth || ball->position.x>m_screenWidth)
	{
		bc->reset();
		m_isResetting = true;
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
	bc = dynamic_cast<BallController*>(ball->getComponent(BallController::tag).getRawPointer());
	m_isResetting = true;
}
