#include "randomPosition.h"

//Returns a random value between zero and max
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

void randomPosition::Serialize(json & j)
{
	j["RandomPosition"] = { {"xRange",xRange},{"yRange",yRange} };
}

//set the random position
void randomPosition::onAddToObject()
{
	gameObject->position.x = (float)randInRange(xRange);
	gameObject->position.y = (float)randInRange(yRange);

}
