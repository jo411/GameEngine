#include "Component.h"

Component::Component()
{	
}

void Component::registerGameObject(GameObject * obj)
{
	gameObject = obj;
}
