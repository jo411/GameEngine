#pragma once
#include "GameObject.h"
#include "Vector2.h"
class GameScene
{
	ListPointer* scene;
	ListPointer* addBuffer;
	ListPointer* removeBuffer;
	bool inUpdate=false;
	void clearBuffers();
	bool dirtyBuffer = false;
public:
	GameScene();
	~GameScene();
	GameObject* CreateGameObject();
	void RemoveGameObject(GameObject* go);
	void update(UpdateParams* params);
	void draw(UpdateParams* params);
};

