#pragma once
#include "GameObject.h"
#include "Vector2.h"
class GameScene
{
	const int DEFAULT_OBJECT_COUNT = 10;
	const int GROWTH_COUNT = 10;
	int objectCount= 0;
	int objectPointer = -1;	
	int size = 0;
	GameObject** objects;
	void growScene();
public:
	GameScene();
	~GameScene();
	GameObject* CreateGameObject(Vector2 position);
	void RemoveGameObject(GameObject* go);
	void update();
};

