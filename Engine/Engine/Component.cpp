#include "Component.h"


Component::Component()
{	
	
}

Component::~Component()
{
		
}

Component::Component(const Component & old)
{
	gameObject = old.gameObject;
}

Component& Component::operator=(const Component& other)
{
	if (this != &other)
	{
		this->gameObject = other.gameObject;
	}
	return *this;
}


//Stores this components attached game object
void Component::registerGameObject(GameObject * obj)
{
	gameObject = obj;
}
