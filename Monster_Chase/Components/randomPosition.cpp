#include "randomPosition.h"

int randomPosition::randInRange(int max)
{
	int multiply = 1;
	if (rand() % 100 + 1 >= 50)
	{
		multiply = -1;
	}
	return (rand() % max + 1)*multiply;
}

randomPosition::randomPosition(int xRange, int yRange)
{
	this->xRange = xRange;
	this->yRange = yRange;
}


randomPosition::~randomPosition()
{
}

void randomPosition::update(UpdateParams * params)
{
}

void randomPosition::draw(UpdateParams * params)
{
}

void randomPosition::onAddToObject()
{
	gameObject->position.x = (float)randInRange(xRange);
	gameObject->position.y = (float)randInRange(yRange);

}
