#include "GameScene.h"
#include "malloc.h"
#include "DataStructures/Lists/ListPointer.h"
#include <vector>
#include <algorithm>
#include "Json/JsonHandler.h"
#include "Physics/RigidBody2d/RigidBody2d.h"
#include "Physics/Collision/CollisionHandler.h"
#include "Physics/AABB/AABB.h"

//Constructs the scene and allocates lists for all the dynamic memory needed
GameScene::GameScene()
{	
	
}

//Clears any dynamic memory allocated
GameScene::~GameScene()
{

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
		sceneVector.erase(std::remove(sceneVector.begin(), sceneVector.end(), gameObject), sceneVector.end());
	}
	else//if this scene is currently updating the object is added to the buffer for later
	{
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
		sceneVector.push_back(addBufferVector[i]);		
	}
	
	addBufferVector.clear();

	for (int i = 0; i < removeBufferVector.size(); i++)
	{		
		sceneVector.erase(std::remove(sceneVector.begin(), sceneVector.end(), removeBufferVector[i]), sceneVector.end());	
	}
	
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

void GameScene::checkCollision(UpdateParams * params)
{
	std::vector<SmartPointer<GameObject>> physObjs;

	for (int i = 0; i < sceneVector.size(); i++)
	{
		//GameObject* obj = ((GameObject*)(scene->getAt(i)));
		SmartPointer<GameObject> obj = sceneVector[i];
		WeakPointer<Component> wptr(obj->getComponent(AABB::tag));
		if (obj->enabled && (wptr.IsAlive()))
		{
			physObjs.push_back(obj);
		}
	}
	if (physObjs.size() > 1)
	{
		CollisionHandler::checkAllObjectsForCollision(physObjs, (float)params->deltaTime);
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

SmartPointer<GameObject> GameScene::getGameObjectByName(std::string name)
{
	SmartPointer<GameObject> obj;	
	for (int i = 0; i < sceneVector.size(); i++)
	{		
		 obj = sceneVector[i];
		 std::string tmp(obj->name->getCharArray());
		 if (tmp.compare(name)==0)
		 {
			 return obj;
		 }		
	}
	SmartPointer<GameObject> nll;
	return nll;
}
