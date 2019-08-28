#include "GameObject.h"

void GameObject::addComponent(Component * newComponent)
{
	newComponent->registerGameObject(this);
	components->add(newComponent);
}

void GameObject::RemoveComponent(GameObject * go)
{
	components->remove(go);
}

void GameObject::update(UpdateParams* params)
{
	for (int i = 0; i <= components->count(); i++)
	{
		Component* obj = ((Component*)(components->getAt(i)));
		if (obj->enabled)
		{
			obj->update(params);
		}
	}
}

void GameObject::draw(UpdateParams * params)
{
	for (int i = 0; i <= components->count(); i++)
	{
		Component* obj = ((Component*)(components->getAt(i)));
		if (obj->enabled)
		{
			obj->draw(params);
		}
	}
}

GameObject::GameObject()
{
	position.x=0;
	position.y = 0;
	components = new ListPointer();
	name = new SimpleString();
}

GameObject::~GameObject()
{
	delete components;
}
