#include "PlayerController.h"
#include "InputManager.h"
#include "GameObject.h"
#include "RigidBody2d.h"
PlayerController::PlayerController(float i_forceMagnitude)
{
	forceMagnitude = i_forceMagnitude;
	timeToApplyForce = 500.0f;
	forceTimer = 0;
}


PlayerController::~PlayerController()
{
}

//checks the input key and moves the player accordingly
void PlayerController::update(UpdateParams * params)
{
	InputManager::Key keyDown = InputManager::lastKeyDown;
	Vector2 moveForce;

	forceTimer += params->deltaTime;
	if (forceTimer > timeToApplyForce)
	{
		forceTimer = 0;
		rb->clearForces();
	}


	if (InputManager::isHeld)
	{
		return;
	}
	if (keyDown == InputManager::Key::W)
	{
		moveForce.y = forceMagnitude;
		InputManager::isHeld = true;
		forceTimer = 0;
	}
	else if (keyDown == InputManager::Key::A)
	{
		moveForce.x = -forceMagnitude;
		InputManager::isHeld = true;
		forceTimer = 0;
	}
	else if (keyDown == InputManager::Key::S)
	{		
		moveForce.y = -forceMagnitude;
		InputManager::isHeld = true;
		forceTimer = 0;
	}
	else if (keyDown == InputManager::Key::D)
	{
		moveForce.x = forceMagnitude;
		InputManager::isHeld = true;
		forceTimer = 0;
	}
	else if (keyDown == InputManager::Key::F)
	{
		rb->clearForces();
		InputManager::isHeld = true;
		forceTimer = 0;
	}
	rb->addForce(moveForce);
	
}

void PlayerController::draw(UpdateParams * params)
{
}

void PlayerController::onAddToObject()
{
	
}

void PlayerController::Serialize(json & j)
{
	j["PlayerController"] = { {"timeToApplyForce",timeToApplyForce},{"forceMagnitude",forceMagnitude} };
}
