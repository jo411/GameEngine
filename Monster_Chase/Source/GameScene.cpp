#include "GameScene.h"
#include "malloc.h"


GameScene::GameScene()
{	
	objects = (GameObject**)malloc(sizeof(GameObject*));
	objects[0] = nullptr;	 
	objectPointer = 0;
	objectCount = 1;
}

GameScene::~GameScene()
{
	//Free each gameobject
	for (int i = 0; i < objectCount; i++)
	{
		free (objects[i]);
	}

	free(objects);
}

GameObject* GameScene::CreateGameObject(Vector2 position)
{
	GameObject* newGameObject =(GameObject*) malloc(sizeof(GameObject));
	objects[objectPointer] = newGameObject;	
	objectPointer++;
	if (objectPointer >= objectCount)
	{
		growScene();
	}
	return newGameObject;
}

void GameScene::RemoveGameObject(GameObject * go)
{

	for (int i = 0; i < objectCount; i++)
	{
		if (objects[i] == go)
		{
			free(objects[i]);			
			objects[i] = objects[objectPointer - 1];
			objects[objectPointer - 1] = nullptr;			
			objectPointer--;
			break;
		}
	}
}

void GameScene::update()
{
	for (int i = 0; i < objectPointer; i++)
	{
		(*(objects[i])).update();
	}
}


void GameScene::growScene()
{
	objectCount += GROWTH_COUNT;
	objects = (GameObject**)realloc(objects, sizeof(GameObject*)*objectCount);

	for (int i = objectPointer; i < objectCount; i++)
	{
		objects[i] = nullptr;
	}
}