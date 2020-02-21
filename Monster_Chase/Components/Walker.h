#pragma once
#include "Component.h"
//This component makes a gameobject move randomly in the scene at a configurable speed
class Walker: public Component
{
	int speed;//how fast it can move
public:
	Walker(int speed);
	~Walker();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);	
	void onAddToObject();
	int getWalkDistance();
	void Serialize(json& j);
};

