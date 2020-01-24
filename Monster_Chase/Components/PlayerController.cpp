#include "PlayerController.h"
#include "InputManager.h"
PlayerController::PlayerController()
{
}


PlayerController::~PlayerController()
{
}

//checks the input key and moves the player accordingly
void PlayerController::update(UpdateParams * params)
{
	InputManager::Key keyDown = InputManager::lastKeyDown;

	if (keyDown == InputManager::Key::W)
	{
		gameObject->position.y++;
	}
	else if (keyDown == InputManager::Key::A)
	{
		gameObject->position.x--;
	}
	else if (keyDown == InputManager::Key::S)
	{
		gameObject->position.y--;
	}
	else if (keyDown == InputManager::Key::D)
	{
		gameObject->position.x++;
	}
}

void PlayerController::draw(UpdateParams * params)
{
}

void PlayerController::onAddToObject()
{
}
