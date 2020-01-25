#pragma once
#include "Component.h"
#include "Vector2.h"
class RigidBody2d : public Component
{
public:
	RigidBody2d();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();

	float mass;
	float drag;	
	void addForce(const Vector2& i_force);
	void clearForces();
private: 
	Vector2 prevPosition;
	Vector2 force;
	Vector2 velocity;
};

