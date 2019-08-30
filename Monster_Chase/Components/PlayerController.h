#pragma once
#include "../Headers/GameObject.h"
//This component allows for keyboard input to move a Game Object
class PlayerController: public Component
{
public:
	PlayerController();
	~PlayerController();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
};

