#pragma once
#include "Component.h"
#include "Vector2.h"
struct CollisionData;
class RigidBody2d : public Component
{
public:
	RigidBody2d();
	void update(UpdateParams* params);

	void physicsUpdate(UpdateParams* params);

	void draw(UpdateParams* params);
	void onAddToObject();

	float mass;
	float drag;	
	float minGroundingSpeed;//speed at which to stop the object

	void Serialize(json & j);
	void addForce(const Vector2& i_force);
	void addImpulse(const Vector2& i_force);	
	void clearForces();	

	void onCollision(CollisionData hit);
	void(*onCollideCallback)(CollisionData) = nullptr;

	const Vector2& getVelocity() { return velocity; }//return the last calculated velocity

	static const std::string tag; 
	virtual const std::string& getTag() { return tag; }
	

private: 
	Vector2 getTotalCurrentForce();
	Vector2 prevPosition;
	Vector2 force;
	Vector2 velocity;
	Vector2 acc;
	Vector2 impulse;
};

