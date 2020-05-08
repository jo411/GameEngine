#pragma once
#include "DataStructures/Pointer/SmartPointer.h"
#include "Entity Component System/GameObject/GameObject.h"
class JsonHandler
{
public:
	static void PopulateGameObjectFromJson(SmartPointer<GameObject> obj, const char * filePath, void(*callback) (SmartPointer<GameObject> obj, json j, std::map<std::string, Component*>& dependencies));
};

