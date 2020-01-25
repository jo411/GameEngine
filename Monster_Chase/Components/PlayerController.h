#pragma once
#include "GameObject.h"
#include "RigidBody2d.h"
//This component allows for keyboard input to move a Game Object
class PlayerController: public Component
{
public:
	PlayerController(float i_speed);
	~PlayerController();
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
	RigidBody2d* rb;//the rigid body to control

private:
	float speed;

};

