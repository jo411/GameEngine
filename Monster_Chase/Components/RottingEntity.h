#pragma once
#include "Component.h"
class RottingEntity: public Component
{
	int turnsToLive;
	int turnCounter = 0;
public:
	RottingEntity(int delay);
	~RottingEntity();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
};

