#include "RigidBody2d.h"
#include "GameObject.h"
#include <Windows.h>
RigidBody2d::RigidBody2d()
{
	velocity.x = 0;
	velocity.y = 0;
	drag = 0;
	mass = 0;
}
void RigidBody2d::update(UpdateParams * params)
{
	Vector2 Acc = (force) / mass;

	float newPosX;
	float newPosY;

	newPosX = 2.0f * gameObject->position.x - prevPosition.x + Acc.x * params->deltaTime;
	newPosY = 2.0f * gameObject->position.y - prevPosition.y + Acc.y * params->deltaTime;

	prevPosition.x = gameObject->position.x;
	prevPosition.y = gameObject->position.y;

	gameObject->position.x = newPosX;
	gameObject->position.y = newPosY;

	velocity.x = newPosX - prevPosition.x;
	velocity.y = newPosY - prevPosition.y;	

	force *= drag;


	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "Current Force: %.9f , %.9f\n", force.x, force.y);
	OutputDebugStringA(Buffer);

}

void RigidBody2d::draw(UpdateParams * params)
{
}

void RigidBody2d::onAddToObject()
{
	prevPosition.x = gameObject->position.x;
	prevPosition.y = gameObject->position.y;
	
}

void RigidBody2d::addForce(const Vector2 & i_force)
{	
	force += i_force;
}

void RigidBody2d::clearForces()
{
	force.x = 0;
	force.y = 0;
}
