#include <iostream>
#include "RottingEntity.h"
#include "GameScene.h"

RottingEntity::RottingEntity(int delay)
{
	this->turnsToLive = delay;
}


RottingEntity::~RottingEntity()
{
}

void RottingEntity::update(UpdateParams * params)
{
	turnCounter++;
	if (turnCounter > turnsToLive)//Kill if the object is past it's expire date
	{		
		std::cout << "~~~"<<*(gameObject->name) << " Has rotted away.~~~\n";
		(gameObject->scene->RemoveGameObject(gameObject));		
	}
}

void RottingEntity::draw(UpdateParams * params)
{
}

void RottingEntity::onAddToObject()
{
}
