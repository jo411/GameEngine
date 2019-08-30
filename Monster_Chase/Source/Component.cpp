#include "Component.h"

Component::Component()
{	
	renderText = new SimpleString();
}

Component::~Component()
{
	delete renderText;
}

//Stores this components attached game object
void Component::registerGameObject(GameObject * obj)
{
	gameObject = obj;
}
