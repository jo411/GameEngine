#pragma once
//This class holds info gathered outside of the scene and passes it through the updates from scene->Gameobject->component
class UpdateParams
{
public:
	char keyPressed;//the key pressed during the most recent frame
	UpdateParams();
	~UpdateParams();
};

