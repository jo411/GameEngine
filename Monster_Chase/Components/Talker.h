#pragma once
#include "Entity Component System/Component/Component.h"
//This component makes a GameObject draw it's name and location to the screen every frame like a renderer for text
class Talker: public Component
{
public:
	Talker();
	~Talker();	
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
};

