#pragma once
#include "SmartPointer.h"
#include "GameObject.h"
class JsonHandler
{
public:
	static void PopulateGameObjectFromJson(SmartPointer<GameObject> obj, const char * filePath, void(*customBindings)(SmartPointer<GameObject> obj, json j));
};

