#include "Component.h"

Component::Component()
{	
	renderText = new SimpleString();
}

Component::~Component()
{
	delete renderText;
}

void Component::registerGameObject(GameObject * obj)
{
	gameObject = obj;
}
