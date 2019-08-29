#pragma once
#include "../Headers/GameObject.h"
class randomPosition : public Component
{
	int xRange;
	int yRange;	
	int randInRange(int max);
public:
	randomPosition(int xRange, int yRange);
	~randomPosition();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
};

