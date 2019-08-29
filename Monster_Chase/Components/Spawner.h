#pragma once
#include "Component.h"
class Spawner : public Component
{
	int turnCounter = 0;
	int delay = 0;
public:
	Spawner(int delay);
	~Spawner();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
};

