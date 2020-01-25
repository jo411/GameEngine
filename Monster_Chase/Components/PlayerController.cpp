#include "PlayerController.h"
#include "InputManager.h"
#include "GameObject.h"
#include "RigidBody2d.h"
PlayerController::PlayerController(float i_speed)
{
	speed = i_speed;
}


PlayerController::~PlayerController()
{
}

//checks the input key and moves the player accordingly
void PlayerController::update(UpdateParams * params)
{
	InputManager::Key keyDown = InputManager::lastKeyDown;
	Vector2 moveForce;
	if (InputManager::isHeld)
	{
		return;
	}
	if (keyDown == InputManager::Key::W)
	{
		moveForce.y = speed;
		InputManager::isHeld = true;
	}
	else if (keyDown == InputManager::Key::A)
	{
		moveForce.x = -speed;
		InputManager::isHeld = true;
	}
	else if (keyDown == InputManager::Key::S)
	{
		rb->clearForces();
		//moveForce.y = -speed;
		InputManager::isHeld = true;
	}
	else if (keyDown == InputManager::Key::D)
	{
		moveForce.x = speed;
		InputManager::isHeld = true;
	}
	rb->addForce(moveForce);
	
}

void PlayerController::draw(UpdateParams * params)
{
}

void PlayerController::onAddToObject()
{
	
}
