#pragma once
#include "../Headers/Component.h"
class Talker: public Component
{
public:
	Talker();
	~Talker();
	void update(UpdateParams* params);
	void onAddToObject();
};

