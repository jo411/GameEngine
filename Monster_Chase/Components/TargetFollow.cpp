#include "TargetFollow.h"
#include "Math/Vector2.h"


TargetFollow::TargetFollow(int moveSpeed, GameObject* target)
{
	speed = moveSpeed;
	setTarget(target);
}


TargetFollow::~TargetFollow()
{
}

void TargetFollow::update(UpdateParams * params)
{
	if (target == nullptr) { return; }

	float dX = target->position.x - gameObject->position.x;
	float dY = target->position.y - gameObject->position.y;

	//Always move in the axis with the greatest distance
	if (abs(dX)>abs(dY))
	{
		if (dX > 0)
		{
			gameObject->position.x += speed;
		}
		else
		{
			gameObject->position.x -= speed;
		}
	}
	else
	{
		if (dY > 0)
		{
			gameObject->position.y += speed;
		}
		else
		{
			gameObject->position.y -= speed;
		}

	}
}

void TargetFollow::draw(UpdateParams * params)
{
}

void TargetFollow::onAddToObject()
{
}

void TargetFollow::setTarget(GameObject * target)
{
	this->target = target;
}

