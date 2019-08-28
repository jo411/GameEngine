#pragma once
#include "GameObject.h"
#include "Vector2.h"
class GameScene
{
	ListPointer* scene;
public:
	GameScene();
	~GameScene();
	GameObject* CreateGameObject();
	void RemoveGameObject(GameObject* go);
	void update(UpdateParams* params);
};

