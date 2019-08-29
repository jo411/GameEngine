#pragma once
#include "UpdateParams.h"
#include "SimpleString.h"
class GameObject;

class Component
{
protected:
	GameObject* gameObject;
	SimpleString* renderText;
public:
	virtual void update(UpdateParams* params) = 0;
	virtual void draw(UpdateParams* params) = 0;
	virtual void onAddToObject() = 0;	
	bool enabled = true;
	Component();
	~Component();
	void registerGameObject(GameObject* obj);
};

