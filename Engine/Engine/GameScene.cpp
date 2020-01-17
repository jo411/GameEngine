#include "GameScene.h"
#include "malloc.h"
#include "ListPointer.h"

//TODO: actually use the rule of three

//Constructs the scene and allocates lists for all the dynamic memory needed
GameScene::GameScene()
{	
	scene = new ListPointer(1);
	addBuffer = new ListPointer(1);
	removeBuffer = new ListPointer(1);
}

//Clears any dynamic memory allocated
GameScene::~GameScene()
{
	//Temporarily using explicit destroy calls for now to avoid weird heap issues
}

//Creates and returns a pointer to a new gameobject that is, or will be, in this scene
GameObject* GameScene::CreateGameObject()
{
	GameObject* newGameObject = new GameObject(this);
	if (!inUpdate)
	{		
		scene->add(newGameObject);		
	}
	else//if this scene is currently updating the object is added to the buffer for later
	{
		addBuffer->add(newGameObject);
		dirtyBuffer = true;//mark the buffers dirty
	}	
	return newGameObject;
}

//Removes the specified gameobject from the scene forever
void GameScene::RemoveGameObject(GameObject * gameObject)
{
	if (!inUpdate)
	{
		scene->remove(gameObject);
	}
	else//if this scene is currently updating the object is added to the buffer for later
	{
		removeBuffer->add(gameObject);
		dirtyBuffer = true;//mark the buffers dirty
	}
}

//Add all objects in the addBuffer and removes all in removeBuffer
void GameScene::clearBuffers()
{
	for (int i = 0; i <= addBuffer->count(); i++)
	{
		scene->add(addBuffer->getAt(i));	
		
	}
	addBuffer->clearNonDestructive();//clear the objects from the list bur keep the memory for more objects later

	for (int i = 0; i <= removeBuffer->count(); i++)
	{
		scene->remove(removeBuffer->getAt(i));
	
	}
	removeBuffer->clearNonDestructive();//clear the objects from the list bur keep the memory for more objects later
	dirtyBuffer = false;//mark the buffers clean
}

//Updates all enabled the gameobjects in this scene
void GameScene::update(UpdateParams* params)
{
	if (dirtyBuffer)//check for any objects in the buffers to process (probably should only use one of these at the end of update)
	{
		clearBuffers();
	}

	inUpdate = true;//lock the gameobject list
	for (int i = 0; i <= scene->count(); i++)//update all enabled Gameobjects in the scene
	{
		GameObject* obj =((GameObject*)(scene->getAt(i)));
		if (obj->enabled)
		{
			obj->update(params);
		}
	}
	inUpdate = false;//unlock the gameobject list

	if (dirtyBuffer)//check for any objects in the buffers to process (probably should only use one of these at the end of update)
	{
		clearBuffers();
	}
}

//Draws all the enabled gameobjects in this scene
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

void GameScene::Release()
{
	delete scene;
	delete addBuffer;
	delete removeBuffer;
}
