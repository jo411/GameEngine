#pragma once
#include "Component.h"
//This component makes its attached gameobject dissapear after a set amount of time. 
class RottingEntity: public Component
{
	int turnsToLive;//How long will this object live
	int turnCounter = 0;//How long this object has been alive
public:
	RottingEntity(int delay);
	~RottingEntity();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
};

