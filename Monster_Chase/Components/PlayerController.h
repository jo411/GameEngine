#pragma once
#include "Entity Component System/GameObject/GameObject.h"
#include "Physics/RigidBody2d/RigidBody2d.h"
//This component allows for keyboard input to move a Game Object
class PlayerController: public Component
{
public:
	PlayerController(float i_forceMagnitude, InputManager::Key i_up, InputManager::Key i_down);
	~PlayerController();
	
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
	void onAddToObject();
	RigidBody2d* rb;//the rigid body to control
	float timeToApplyForce;
	float forceTimer;//how many miliseconds to apply force for
	void Serialize(json & j);	
	static const std::string tag;
	virtual const std::string& getTag() { return tag; }

private:
	float forceMagnitude;//how many (newtons?) of force to apply
	InputManager::Key m_upKey;
	InputManager::Key m_downKey;
};

