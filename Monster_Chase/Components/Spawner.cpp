#include <iostream>
#include "Spawner.h"
#include "GameObject.h"
#include "../Headers/GameScene.h"
#include "Talker.h"
#include "Spawner.h"
#include "Walker.h"
#include "RottingEntity.h"
Spawner::Spawner(int delay)
{
	this->delay = delay;
}


Spawner::~Spawner()
{
}

void Spawner::update(UpdateParams * params)
{
	turnCounter++;
	if (turnCounter >= delay)
	{
		turnCounter = 0;
		GameObject* monster = (gameObject->scene->CreateGameObject());
		monster->name->fromCharArray("Hive Spawn");
		monster->addComponent(new Talker());
		monster->addComponent(new Walker(3));
		monster->addComponent(new RottingEntity(5));
		monster->position.x = gameObject->position.x;
		monster->position.y = gameObject->position.y;		
		renderText->fromCharArray("~~~A hive just spawned a new monster!~~~\n");
	}
	else
	{
		renderText->fromCharArray("");
	}
	

}

void Spawner::draw(UpdateParams * params)
{
	if (delay - turnCounter == 1)
	{
		std::cout << "~~~" << *(gameObject->name) << " is about to spawn a creature at: " << gameObject->position << "~~~\n";
	}
	std::cout << *renderText;
}

void Spawner::onAddToObject()
{
}
