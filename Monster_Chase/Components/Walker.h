#pragma once
#include "Component.h"
class Walker: public Component
{
	int speed;
public:
	Walker(int speed);
	~Walker();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
	int getWalkDistance();
};

