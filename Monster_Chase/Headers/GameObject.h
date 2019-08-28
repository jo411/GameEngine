#pragma once
#include "ListPointer.h"
#include "Component.h"
#include "Vector2.h"
#include "SimpleString.h"
class GameObject
{
	ListPointer* components;
public:
	SimpleString* name;
	Vector2 position;
	void addComponent(Component* newComponent);
	void RemoveComponent(GameObject* go);
	bool enabled = true;
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	GameObject();
	~GameObject();
};

