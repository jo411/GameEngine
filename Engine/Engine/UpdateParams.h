#pragma once
#include "InputManager.h"
//This class holds info gathered outside of the scene and passes it through the updates from scene->Gameobject->component
class UpdateParams
{
public:
	
	UpdateParams();
	~UpdateParams();
	const InputManager* getInput() { return &input; };
private:
	InputManager input;
};

