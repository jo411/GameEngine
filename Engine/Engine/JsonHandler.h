#pragma once
#include "SmartPointer.h"
#include "GameObject.h"
class JsonHandler
{
public:
	static void PopulateGameObjectFromJson(SmartPointer<GameObject> obj, const char * filePath, void(*callback) (SmartPointer<GameObject> obj, json j, std::map<std::string, Component*>& dependencies));
};

