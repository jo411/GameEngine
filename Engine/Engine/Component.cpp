#include "Component.h"

Component::Component()
{	
	renderText = new SimpleString();
}

Component::~Component()
{
	delete renderText;
}

Component::Component(const Component & old)
{
	renderText = new SimpleString();
}

Component & Component::operator=(const Component & other)
{
	 if (this != &other)
	{
		 renderText->fromCharArray(other.renderText->getCharArray);
	}
	 return *this;
}

//Stores this components attached game object
void Component::registerGameObject(GameObject * obj)
{
	gameObject = obj;
}
