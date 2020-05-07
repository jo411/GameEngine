#include "BallController.h"
#include "../Engine/Physics/CollisionHandler.h"
const std::string BallController::tag = "ballcontroller";
BallController::BallController()
{
	speed = Vector2(.07f, .001f);
}

BallController::~BallController()
{
}

void BallController::update(UpdateParams * params)
{
}

void BallController::draw(UpdateParams * params)
{
}

void BallController::onAddToObject()
{
}

void BallController::Serialize(json & j)
{
}

void BallController::reset()
{
	rb->clearForces();
	gameObject->position = Vector2(0, 0);
}

void BallController::launch()
{
	Vector2 force;
	force.x = speed.x;
	force.y = speed.y;
	

	if (rand() % 100 + 1 >= 50)
	{
		force.x *= -1;
	}
	if (rand() % 100 + 1 >= 50)
	{
		force.y *= -1;
	}
	
	rb->addForce(force);
}
