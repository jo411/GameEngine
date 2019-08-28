#include "GameObject.h"

void GameObject::addComponent(Component * newComponent)
{
	components->add(newComponent);
}

void GameObject::RemoveComponent(GameObject * go)
{
	components->remove(go);
}

void GameObject::update()
{
	for (int i = 0; i < components->count(); i++)
	{
		Component* obj = ((Component*)(components->getAt(i)));
		if (obj->enabled)
		{
			obj->update();
		}
	}
}

GameObject::GameObject()
{
	position.x=0;
	position.y = 0;
	components = new ListPointer();
}

GameObject::~GameObject()
{
	delete components;
}
