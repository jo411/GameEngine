#pragma once
#include "Entity Component System/GameObject/GameObject.h"
#include "Physics/RigidBody2d/RigidBody2d.h"
class BallController : public Component
{
public:
	BallController(float i_speedX, float i_speedY);
	~BallController();

	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
	RigidBody2d* rb;//the rigid body to control	
	void Serialize(json & j);	
	void reset();
	void launch();
	Vector2 speed;

	static const std::string tag;
	virtual const std::string& getTag() { return tag; }

private:

};

