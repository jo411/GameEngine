#include "RigidBody2d.h"
#include "GameObject.h"
#include <Windows.h>
#include "Physics/CollisionHandler.h"
#include "../GLib/_Console/ConsolePrint.h"
#include "Floats.h"
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
}

void RigidBody2d::physicsUpdate(UpdateParams * params)
{
	
	//Slightly modified verlet called Velocity Verlet

	float dt = (float)params->deltaTime;
	acc = getTotalCurrentForce() / mass;

	//Check for min speed and ground the object if needed
	if (abs(velocity.x) < minGroundingSpeed &&abs(acc.x) < .0001)
	{
		velocity.x = 0;
		impulse.x = 0;
	}

	if (abs(velocity.y) < minGroundingSpeed && abs(acc.y) < .0001)
	{
		velocity.y = 0;
		impulse.y = 0;
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


	impulse.x *= drag * dt;
	impulse.y *= drag * dt;

}

void RigidBody2d::refresh()
{
		clearForces();
		velocity = SavedVelocity;
		addForce(SavedForce);	
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

void RigidBody2d::addImpulse(const Vector2 & i_force)
{
	impulse += i_force;
}

void RigidBody2d::clearForces()
{
	force.x = 0;
	force.y = 0;
	impulse.x = 0;
	impulse.y = 0;
}

void RigidBody2d::Serialize(json & j)
{
	j["RigidBody2d"] = { {"mass",mass},{"drag", drag},{"minGroundingSpeed",minGroundingSpeed } };
}

void RigidBody2d::onCollision(CollisionData& hit)
{
	if (!canCollide) { return; }

	if (physicsType == 0)//full conservation
	{
		float m1;
		float m2;

		Vector2 v1;
		Vector2 v2;

		Vector2 v1Prime;
		if (hit.A == gameObject)//determine which part of the collision this GO is
		{
			RigidBody2d* rbOther = dynamic_cast<RigidBody2d*>(hit.B->getComponent(RigidBody2d::tag).getRawPointer());
			m1 = mass;
			m2 = rbOther->mass;
			v1 = velocity;
			v2 = rbOther->getVelocity();
			float partA = (m1 - m2) / (m1 + m2);
			float partB = (2 * m2) / (m1 + m2);

			v1Prime.x = partA * v1.x + partB * v2.x;

			v1Prime.y = partA * v1.y + partB * v2.y;

		}
		else
		{
			RigidBody2d* rbOther = dynamic_cast<RigidBody2d*>(hit.A->getComponent(RigidBody2d::tag).getRawPointer());
			m1 = rbOther->mass;
			m2 = mass;
			v1 = rbOther->getVelocity();
			v2 = velocity;

			float partA = (2 * m1) / (m1 + m2);
			float partB = (m2 - m1) / (m1 + m2);

			v1Prime.x = partA * v1.x + partB * v2.x;

			v1Prime.y = partA * v1.y + partB * v2.y;
		}

		float KEX = .5f*mass*v1Prime.getX()*v1Prime.getX();
		float KEY = .5f*mass*v1Prime.getY()*v1Prime.getY();
		float stoppingDistance = 2;

		Vector2 newForce;
		newForce.x = KEX / stoppingDistance;
		newForce.y = KEY / stoppingDistance;

		Vector2 reflectedForce;

		int velocitySignx = signbit(velocity.x) ? -1 : 1;
		int velocitySigny = signbit(velocity.y) ? -1 : 1;
		//the axis is either x or y

		if (Floats::isZero(hit.CollisionAxis.X()))
		{

			reflectedForce.x = -velocitySignx * newForce.x;
			reflectedForce.y = velocitySigny * newForce.y;
		}
		else
		{
			reflectedForce.x = velocitySignx * newForce.x;
			reflectedForce.y = -velocitySigny * newForce.y;
		}
		SavedVelocity = v1Prime;
		SavedForce = reflectedForce;

	}
	else if (physicsType == 1)//simple pure reflection
	{
		RigidBody2d* rbOther;
		if (hit.A == gameObject)
		{
			rbOther = dynamic_cast<RigidBody2d*>(hit.B->getComponent(RigidBody2d::tag).getRawPointer());
		}
		else
		{
			rbOther = dynamic_cast<RigidBody2d*>(hit.A->getComponent(RigidBody2d::tag).getRawPointer());
		}

		Vector2 reflectedForce;

		Vector2 newForce = Vector2(abs(force.x), abs(force.y));

		int velocitySignx = signbit(force.x) ? -1 : 1;
		int velocitySigny = signbit(force.y) ? -1 : 1;
		if (Floats::isZero(hit.CollisionAxis.X()))
		{

			reflectedForce.x = -velocitySignx * newForce.x;
			reflectedForce.y = velocitySigny * newForce.y;
		}
		else
		{
			reflectedForce.x = velocitySignx * newForce.x;
			reflectedForce.y = -velocitySigny * newForce.y;
		}
		float additionalForce = .1f*rbOther->force.y;

		SavedVelocity = Vector2(0, 0);
		SavedForce = reflectedForce + Vector2(0, additionalForce);

	}
}




void RigidBody2d::onCollideSimpleReflect(CollisionData hit)
{
	RigidBody2d* rb = dynamic_cast<RigidBody2d*>(hit.A->getComponent(RigidBody2d::tag).getRawPointer());
	RigidBody2d* rbOther = dynamic_cast<RigidBody2d*>(hit.B->getComponent(RigidBody2d::tag).getRawPointer());
	RigidBody2d* collider = nullptr;
	if (rb->canCollide)
	{
		collider = rb;
		Vector2 reflectedForce;

		Vector2 newForce = collider->velocity;

		int velocitySignx = signbit(collider->velocity.x) ? -1 : 1;
		int velocitySigny = signbit(collider->velocity.y) ? -1 : 1;
		if (Floats::isZero(hit.CollisionAxis.X()))
		{

			reflectedForce.x = -velocitySignx * newForce.x;
			reflectedForce.y = velocitySigny * newForce.y;
		}
		else
		{
			reflectedForce.x = velocitySignx * newForce.x;
			reflectedForce.y = -velocitySigny * newForce.y;
		}
		collider->SavedVelocity = Vector2(0, 0);
		collider->SavedForce = reflectedForce;
	}
}

void RigidBody2d::freeze()
{
	clearForces();
	velocity = Vector2(0, 0);
}
	
	

Vector2 RigidBody2d::getTotalCurrentForce()
{
	return force + impulse;
}
