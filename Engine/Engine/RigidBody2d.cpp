#include "RigidBody2d.h"
#include "GameObject.h"
#include <Windows.h>
const std::string RigidBody2d::tag = "rigidbody";
RigidBody2d::RigidBody2d()
{
	velocity.x = 0;
	velocity.y = 0;
	acc.x = 0;
	acc.y = 0;
	drag = 0;
	mass = 0;
}
void RigidBody2d::update(UpdateParams * params)
{
	//Slightly modified verlet called Velocity Verlet

	float dt =(float)params->deltaTime;
	acc = force / mass;

	//Check for min speed and ground the object if needed
	if (abs(velocity.x) < minGroundingSpeed &&abs(acc.x)<.0001)
	{
		velocity.x = 0;
	}

	if (abs(velocity.y) < minGroundingSpeed && abs(acc.y) < .0001)
	{
		velocity.y = 0;
	}

	//verlet integration

	Vector2 newPos = gameObject->position + velocity * dt + acc * (dt*dt*.5);
	
	Vector2 dragForce;
	dragForce.x = (float)(0.5 * drag * (velocity.x * abs(velocity.x)));
	dragForce.y = (float)(0.5 * drag * (velocity.y * abs(velocity.y)));
	Vector2 dragAcc = dragForce / mass;

	Vector2 gravity;
	gravity.x = 0;
	gravity.y = 0;

	Vector2 newAcc = gravity - dragAcc;
	Vector2 newVel = velocity + (acc + newAcc)*(dt*.5);

	gameObject->position.x = newPos.x;
	gameObject->position.y = newPos.y;	

	velocity = newVel;
	acc = newAcc;

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
void RigidBody2d::Serialize(json & j)
{
	j["RigidBody2d"] = { {"mass",mass},{"drag", drag},{"minGroundingSpeed",minGroundingSpeed } };
}