#include "Walker.h"
#include "Engine\GameObject.h"
Walker::Walker(int speed)
{
	this->speed = speed;
}


Walker::~Walker()
{
}

void Walker::update(UpdateParams * params)
{
	//50% to move in either axis 
	if (rand() % 101 >= 50)
	{
		gameObject->position.x += getWalkDistance();
	}
	else
	{
		gameObject->position.y += getWalkDistance();
	}	
	
}

void Walker::draw(UpdateParams * params)
{
}

void Walker::onAddToObject()
{
}

//returns + or - speed at random
int Walker::getWalkDistance()
{
	int multiply = 1;
	if (rand() % 100 + 1 >= 50)
	{
		multiply = -1;
	}
	return speed * multiply;
}
