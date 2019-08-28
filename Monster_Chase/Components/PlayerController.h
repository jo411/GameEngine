#pragma once
#include "../Headers/GameObject.h"
class PlayerController: public Component
{
public:
	PlayerController();
	~PlayerController();
	void update(UpdateParams* params);
	void onAddToObject();
};

