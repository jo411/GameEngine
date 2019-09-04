#pragma once
#include "Engine\Component.h"
//This component will spawn creaters at its location at a configurable rate
class Spawner : public Component
{
	int turnCounter = 0;//how many turns since last spawn 
	int delay = 0;//How long to wait between spawns
public:
	Spawner(int delay);
	~Spawner();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
};

