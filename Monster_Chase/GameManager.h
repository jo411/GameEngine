#pragma once
#include "GameObject.h"
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
	bool initialized = false;
	void onStart();
	static const std::string tag;
	virtual const std::string& getTag() { return tag; }	

	float m_timeToReset;
	

private:
	SmartPointer<GameObject> ball;
	BallController* bc;
	float m_resetTimer = 0;
	bool m_isResetting = false;
	float m_screenWidth;

	
};

