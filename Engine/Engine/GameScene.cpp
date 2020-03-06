#include "GameScene.h"
#include "malloc.h"
#include "ListPointer.h"
#include <vector>
#include <algorithm>
#include "JsonHandler.h"

//TODO: actually use the rule of three

//Constructs the scene and allocates lists for all the dynamic memory needed
GameScene::GameScene()
{	
	//scene = new ListPointer(1);
	//addBuffer = new ListPointer(1);
	//removeBuffer = new ListPointer(1);
}

//Clears any dynamic memory allocated
GameScene::~GameScene()
{
	//Temporarily using explicit destroy calls for now to avoid weird heap issues
}

//Creates and returns a pointer to a new gameobject that is, or will be, in this scene
WeakPointer<GameObject> GameScene::CreateGameObject()
{
	SmartPointer<GameObject> newGameObject( new GameObject(this));
	
	Engine::ScopeLock Lock(addBufferMutex);
		addBufferVector.push_back(newGameObject);

		dirtyBuffer = true;//mark the buffers dirty		
		
	return newGameObject;
}

void GameScene::CreateGameObjectFromJsonAsync(const char * AssetFilePath, void(*callback) (SmartPointer<GameObject> obj, json j, std::map<std::string, Component*>& dependencies))
{	
	SmartPointer<GameObject> newGameObject(new GameObject(this));
	JsonHandler::PopulateGameObjectFromJson(newGameObject, AssetFilePath, callback);

	Engine::ScopeLock Lock(addBufferMutex);
	addBufferVector.push_back(newGameObject);

	dirtyBuffer = true;//mark the buffers dirty	
}

//Removes the specified gameobject from the scene forever
void GameScene::RemoveGameObject(SmartPointer<GameObject> gameObject)
{
	if (!inUpdate)
	{
		//scene->remove(gameObject);
	
		sceneVector.erase(std::remove(sceneVector.begin(), sceneVector.end(), gameObject), sceneVector.end());
	}
	else//if this scene is currently updating the object is added to the buffer for later
	{
		//removeBuffer->add(gameObject);

		removeBufferVector.push_back(gameObject);
		
		dirtyBuffer = true;//mark the buffers dirty
	}
}

//Add all objects in the addBuffer and removes all in removeBuffer
void GameScene::clearBuffers()
{
	Engine::ScopeLock Lock(addBufferMutex);
	for (int i = 0; i < addBufferVector.size(); i++)
	{
		//scene->add(addBuffer->getAt(i));

		sceneVector.push_back(addBufferVector[i]);
		
	}
	//addBuffer->clearNonDestructive();//clear the objects from the list bur keep the memory for more objects later
	addBufferVector.clear();

	for (int i = 0; i < removeBufferVector.size(); i++)
	{
		//scene->remove(removeBuffer->getAt(i));

		sceneVector.erase(std::remove(sceneVector.begin(), sceneVector.end(), removeBufferVector[i]), sceneVector.end());
	
	}
	//removeBuffer->clearNonDestructive();//clear the objects from the list bur keep the memory for more objects later
	removeBufferVector.clear();
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
	for (int i = 0; i < sceneVector.size(); i++)//update all enabled Gameobjects in the scene
	{
//		GameObject* obj =((GameObject*)(scene->getAt(i)));
		SmartPointer<GameObject> obj = sceneVector[i];

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
	for (int i = 0; i <sceneVector.size(); i++)
	{
		//GameObject* obj = ((GameObject*)(scene->getAt(i)));
		SmartPointer<GameObject> obj = sceneVector[i];
		if (obj->enabled)
		{
			obj->draw(params);
		}
	}
}

void GameScene::Release()
{
	//delete scene;
	//delete addBuffer;
	//delete removeBuffer;

	Engine::ScopeLock Lock(addBufferMutex);
	sceneVector.clear();
	addBufferVector.clear();
	removeBufferVector.clear();

}
