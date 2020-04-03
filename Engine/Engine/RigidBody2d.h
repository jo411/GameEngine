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
	float minGroundingSpeed;//speed at which to stop the object

	void Serialize(json & j);
	void addForce(const Vector2& i_force);
	void clearForces();

	static const std::string tag; // derived::pic
	virtual const std::string& getTag() { return tag; }
	

private: 
	Vector2 prevPosition;
	Vector2 force;
	Vector2 velocity;
	Vector2 acc;
};

