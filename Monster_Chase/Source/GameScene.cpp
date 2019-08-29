#include "GameScene.h"
#include "malloc.h"
#include "ListPointer.h"

//TODO: actually use the rule of three


GameScene::GameScene()
{	
	scene = new ListPointer(1);
	addBuffer = new ListPointer(1);
	removeBuffer = new ListPointer(1);
}

GameScene::~GameScene()
{
	delete scene;
	delete addBuffer;
	delete removeBuffer;
}

GameObject* GameScene::CreateGameObject()
{
	GameObject* newGameObject = new GameObject(this);
	if (!inUpdate)
	{		
		scene->add(newGameObject);		
	}
	else
	{
		addBuffer->add(newGameObject);
		dirtyBuffer = true;
	}	
	return newGameObject;

}

void GameScene::RemoveGameObject(GameObject * gameObject)
{
	if (!inUpdate)
	{
		scene->remove(gameObject);
	}
	else
	{
		removeBuffer->add(gameObject);
		dirtyBuffer = true;
	}
}


void GameScene::clearBuffers()
{
	for (int i = 0; i <= addBuffer->count(); i++)
	{
		scene->add(addBuffer->getAt(i));	
		
	}
	addBuffer->clearNonDestructive();

	for (int i = 0; i <= removeBuffer->count(); i++)
	{
		scene->remove(removeBuffer->getAt(i));
	
	}
	removeBuffer->clearNonDestructive();
	dirtyBuffer = false;
}

void GameScene::update(UpdateParams* params)
{
	if (dirtyBuffer)
	{
		clearBuffers();
	}
	inUpdate = true;
	for (int i = 0; i <= scene->count(); i++)
	{
		GameObject* obj =((GameObject*)(scene->getAt(i)));
		if (obj->enabled)
		{
			obj->update(params);
		}
	}
	inUpdate = false;

	if (dirtyBuffer)
	{
		clearBuffers();
	}
}

void GameScene::draw(UpdateParams* params)
{
	for (int i = 0; i <= scene->count(); i++)
	{
		GameObject* obj = ((GameObject*)(scene->getAt(i)));
		if (obj->enabled)
		{
			obj->draw(params);
		}
	}
}
