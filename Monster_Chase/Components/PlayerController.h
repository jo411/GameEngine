#pragma once
#include "GameObject.h"
#include "RigidBody2d.h"
//This component allows for keyboard input to move a Game Object
class PlayerController: public Component
{
public:
	PlayerController(float i_forceMagnitude);
	~PlayerController();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
	RigidBody2d* rb;//the rigid body to control
	float timeToApplyForce;
	float forceTimer;//how many miliseconds to apply force for
private:
	float forceMagnitude;//how many (newtons?) of force to apply

};

