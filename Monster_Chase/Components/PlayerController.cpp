#include "PlayerController.h"
PlayerController::PlayerController()
{
}


PlayerController::~PlayerController()
{
}

//checks the input key and moves the player accordingly
void PlayerController::update(UpdateParams * params)
{
	if (params->keyPressed == 'w')
	{
		gameObject->position.y++;
	}
	else if (params->keyPressed == 'a')
	{
		gameObject->position.x--;
	}
	else if (params->keyPressed == 's')
	{
		gameObject->position.y--;
	}
	else if (params->keyPressed == 'd')
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
