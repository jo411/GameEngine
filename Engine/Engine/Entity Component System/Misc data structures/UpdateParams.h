#pragma once
#include "Input/InputManager.h"
//This class holds info gathered outside of the scene and passes it through the updates from scene->Gameobject->component
class UpdateParams
{
public:
	double deltaTime;
	UpdateParams();
	~UpdateParams();
};

