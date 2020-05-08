#include "JsonHandler.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "Rendering/RenderingComponent/SpriteRenderer.h"
#include "Physics/RigidBody2d/RigidBody2d.h"
#include "Physics/AABB/AABB.h"



void JsonHandler::PopulateGameObjectFromJson(SmartPointer<GameObject> obj, const char * filePath, void(*callback) (SmartPointer<GameObject> obj, json j, std::map<std::string, Component*>& dependencies))
{
	std::map<std::string, Component*> dependencies;//save all components incase another needs a reference
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
		std::string file = j2["FileName"];		
		SpriteRenderer* newComp = new SpriteRenderer(file.c_str());
		dependencies.emplace("SpriteRenderer", newComp);
		obj->addComponent(newComp);
	}
	
	if (j.contains("RigidBody2d"))
	{
		json j2 = j["RigidBody2d"];
		float drag = j2["drag"];
		float mass = j2["mass"];
		float minGroundingSpeed = j2["minGroundingSpeed"];
		bool canCollide = j2["canCollide"];
		int physicsType = j2["physicsType"];

		RigidBody2d* rb = new RigidBody2d();
		rb->drag = drag;
		rb->mass = mass;
		rb->minGroundingSpeed = minGroundingSpeed;
		rb->physicsType = physicsType;
		rb->canCollide = canCollide;

		dependencies.emplace("RigidBody2d", rb);

		obj->addComponent(rb);		
	}
	
	if (j.contains("AABB"))
	{
		json j2 = j["AABB"];

		float EX = j2["EX"];
		float EY = j2["EY"];

		float CX = j2["CX"];
		float CY = j2["CY"];


		AABB* aabb = new AABB(CX, CY, EX, EY);

		dependencies.emplace("AABB", aabb);

		obj->addComponent(aabb);

	}


	callback(obj, j,dependencies);
	
}
