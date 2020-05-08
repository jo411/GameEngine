#pragma once
#include "GameObject.h"
class GameManager : public Component
{
public:
	GameManager();
	~GameManager();

	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
	
	void Serialize(json & j);	

	static const std::string tag;
	virtual const std::string& getTag() { return tag; }
	static const std::string tag;
	virtual const std::string& getTag() { return tag; }
private:

};

