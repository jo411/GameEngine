#include "JsonHandler.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "SpriteRenderer.h"



void JsonHandler::PopulateGameObjectFromJson(SmartPointer<GameObject> obj, const char * filePath)
{
	std::map<char*, Component*> dependencies;//save all components incase another needs a reference
	std::ifstream ifs(filePath);
	json j = json::parse(ifs);	

	if (j.contains("Name"))
	{
		std::string name = j["Name"];
		obj->name->fromCharArray(name.c_str());
	}

	if (j.contains("Position"))
	{
		json j2 = j["Position"];		
		obj->position.x=j2["x"];
		obj->position.y = j2["y"];
	}

	if (j.contains("SpriteRenderer"))
	{
		json j2 = j["SpriteRenderer"];
		//Sprite
	}
	
		
	
}
