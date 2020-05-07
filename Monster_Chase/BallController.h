#pragma once
#include "GameObject.h"
#include "RigidBody2d.h"
class BallController : public Component
{
public:
	BallController();
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

