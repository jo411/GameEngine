#pragma once
#include "Entity Component System/GameObject/GameObject.h"
#include "Entity Component System/Component/Component.h"
//This component starts a GameObject at a random location 
class randomPosition : public Component
{
	int xRange;// +/- range on x axis from zero
	int yRange;	// +/- range on x axis from zero
	int randInRange(int max);
public:
	randomPosition(int xRange, int yRange);
	~randomPosition();
	void update(UpdateParams* params);	
	void draw(UpdateParams* params);
	void Serialize(json & j);
	void onAddToObject();
};

