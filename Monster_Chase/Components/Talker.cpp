#include "Talker.h"
#include "../Headers/GameObject.h"
#include <iostream>
Talker::Talker()
{
}


Talker::~Talker()
{
}

void Talker::draw(UpdateParams * params)
{
	std::cout << ((SimpleString)(*gameObject->name)) << " is at " <<gameObject->position << "\n";
}
void Talker::update(UpdateParams* params)
{	
}

void Talker::onAddToObject()
{
}


