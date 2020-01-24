#include "RigidBody2d.h"
#include "GameObject.h"
void RigidBody2d::update(UpdateParams * params)
{
	Vector2 dragForce;
	dragForce.x = -drag * velocity.x*velocity.x;
	dragForce.y = -drag * velocity.y*velocity.y;

	force += dragForce;
	Vector2 Acc = force / mass;

	float newPosX;
	float newPosY;

	newPosX = 2 * gameObject->position.x - prevPosition.x + Acc.x * params->deltaTime;
	newPosY = 2 * gameObject->position.y - prevPosition.y + Acc.y * params->deltaTime;

	prevPosition.x = gameObject->position.x;
	prevPosition.y = gameObject->position.y;

	gameObject->position.x = newPosX;
	gameObject->position.y = newPosY;

	velocity.x = newPosX - prevPosition.x;
	velocity.y = newPosY - prevPosition.y;

}

void RigidBody2d::draw(UpdateParams * params)
{
}

void RigidBody2d::onAddToObject()
{
	prevPosition.x = gameObject->position.x;
	prevPosition.y = gameObject->position.y;

	velocity.x = 0;
	velocity.y = 0;
	
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
