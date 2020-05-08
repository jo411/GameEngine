#pragma once
#include "Entity Component System/GameObject/GameObject.h"
#include "BallController.h"
class GameManager : public Component
{
public:
	GameManager(const float& i_resetTime, const float& i_width);
	~GameManager();

	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();		
	void Serialize(json & j);	

	bool m_initialized = false;
	bool m_matchIsRunning = false;
	bool onStart();
	void updateScore();
	void stopMatch();
	void startMatch();
	static const std::string tag;
	virtual const std::string& getTag() { return tag; }	

	float m_timeToReset;
	
	int m_p1Score = 0;
	int m_p2Score = 0;



private:
	SmartPointer<GameObject> ball;
	SmartPointer<GameObject> splash;
	SmartPointer<GameObject> p1Help;
	SmartPointer<GameObject> p2Help;

	BallController* bc;
	float m_resetTimer = 0;
	bool m_isResetting = false;
	float m_screenWidth;

	SmartPointer<GameObject> p1[5];//contains sprites for scores and winning in this order: //0//1//2//3//win
	SmartPointer<GameObject> p2[5];
	
};

