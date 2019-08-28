#include "GameScene.h"
#include "malloc.h"
#include "ListPointer.h"

//TODO: actually use the rule of three

GameScene::GameScene()
{	
	scene = new ListPointer();
}

GameScene::~GameScene()
{
	delete scene;
}

GameObject* GameScene::CreateGameObject()
{
	GameObject* newGameObject =(GameObject*) malloc(sizeof(GameObject));
	
	scene->add(newGameObject);

	return newGameObject;

}

void GameScene::RemoveGameObject(GameObject * gameObject)
{
	scene->remove(gameObject);
	
}

void GameScene::update()
{
	for (int i = 0; i < scene->count(); i++)
	{
		GameObject* obj =((GameObject*)(scene->getAt(i)));
		if (obj->enabled)
		{
			obj->update();
		}
	}
}
