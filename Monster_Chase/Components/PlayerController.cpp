#include "PlayerController.h"
#include "InputManager.h"
#include "GameObject.h"
#include "RigidBody2d.h"
const std::string PlayerController::tag = "playercontroller";
PlayerController::PlayerController(float i_forceMagnitude, InputManager::Key i_up, InputManager::Key i_down)
{
	forceMagnitude = i_forceMagnitude;
	timeToApplyForce = 500.0f;
	forceTimer = 0;
	m_upKey = i_up;
	m_downKey = i_down;
}


PlayerController::~PlayerController()
{
}

//checks the input key and moves the player accordingly
void PlayerController::update(UpdateParams * params)
{
	InputManager::Key keyDown = InputManager::lastKeyDown;
	Vector2 moveForce;

	forceTimer += (float)params->deltaTime;
	if (forceTimer > timeToApplyForce)
	{
		forceTimer = 0;
		rb->clearForces();
	}


	if (InputManager::isHeld)
	{
		return;
	}
	if (keyDown ==m_upKey)
	{
		moveForce.y = forceMagnitude;
		InputManager::isHeld = true;
		forceTimer = 0;
	}	
	else if (keyDown == m_downKey)
	{		
		moveForce.y = -forceMagnitude;
		InputManager::isHeld = true;
		forceTimer = 0;
	}	
	else if (keyDown == InputManager::Key::F)
	{
		/*rb->clearForces();
		InputManager::isHeld = true;
		forceTimer = 0;*/
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
