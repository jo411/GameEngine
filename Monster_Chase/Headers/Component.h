#pragma once
#include "UpdateParams.h"
class GameObject;

class Component
{
protected:
	GameObject* gameObject;
public:
	virtual void update(UpdateParams* params) = 0;
	virtual void onAddToObject() = 0;
	bool enabled = true;
	Component();
	void registerGameObject(GameObject* obj);
};

