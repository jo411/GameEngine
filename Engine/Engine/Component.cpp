#include "Component.h"


Component::Component()
{	
	
}

Component::~Component()
{
		
}

//Stores this components attached game object
void Component::registerGameObject(GameObject * obj)
{
	gameObject = obj;
}
