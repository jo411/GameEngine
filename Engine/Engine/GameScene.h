#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include <vector>
#include "SmartPointer.h"
#include "WeakPointer.h"
//The game scene is where all the gameobjects live. It manages creation, removal, updating, and drawing of objects. It is the access point to the game.
class GameScene
{
	std::vector<SmartPointer<GameObject>> sceneVector;
	std::vector<SmartPointer<GameObject>> addBufferVector;
	std::vector<SmartPointer<GameObject>> removeBufferVector;

	//ListPointer* scene;//A list to all the gameobjects in this scene
	//ListPointer* addBuffer;//A list of gameobjects added during an update
	//ListPointer* removeBuffer;//A list of gameobjects removed during an update

	bool inUpdate=false;//Is this scene currently updating
	void clearBuffers();//Add all objects in the addBuffer and removes all in removeBuffer after an update finishes
	bool dirtyBuffer = false;//Have the buffers been modified during an update	
public:
	GameScene();
	~GameScene();
	WeakPointer<GameObject> CreateGameObject();//Creates and returns a pointer to a new gameobject that is, or will be, in this scene
	WeakPointer<GameObject> CreateGameObject(const char* AssetFilePath, void(*callback) (SmartPointer<GameObject> obj, json j, std::map<std::string, Component*>& dependencies));
	void RemoveGameObject(SmartPointer<GameObject> go);//Removes the specified gameobject from the scene forever
	void update(UpdateParams* params);//Updates all the enabled gameobjects in this scene
	void draw(UpdateParams* params);//Draws all the enabled gameobjects in this scene
	void Release();//Forces all game objects to destruct. This makes the scene unusable so only use on cleanup. 
};

