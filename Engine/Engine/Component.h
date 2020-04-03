#pragma once
#include "UpdateParams.h"
#include "SimpleString.h"
#include <nlohmann/json.hpp>
#include <string>
using json = nlohmann::json;
class GameObject;

//The component class is attached to a game object and is updated when the gameobject revieves an update to modify its game objects behavior
	class Component
	{
	protected:
		GameObject* gameObject=NULL;//What G.O. is this component attached to		
	public:
		virtual void update(UpdateParams* params) = 0;//defined in a derived class. Is called with its gameobject's update
		virtual void draw(UpdateParams* params) = 0;//defined in a derived class. Is called with its gameobject's draw
		virtual void onAddToObject() = 0;	//Defined in a derived class. Is called after a component is added to a gameobject
		virtual void Serialize(json& j);
		bool enabled = true; //will this component recieve or ignore updates. 
		Component();
		virtual ~Component();	
		Component(const Component &old);
		Component& operator=(const Component& other);
		void registerGameObject(GameObject* obj);//Stores this components attached game object
		static const std::string tag;
		virtual const std::string& getTag() { return tag; }
	};



