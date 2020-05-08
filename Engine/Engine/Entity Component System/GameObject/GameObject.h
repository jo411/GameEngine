#pragma once
#include "../Component/Component.h"
#include "../Engine/Engine/Math/Vector2.h"
#include "../Engine/Engine/DataStructures/Strings/SimpleString.h"
#include <nlohmann/json.hpp>
#include "../Engine/Engine/Math/Matrix4.h"
#include <string>
#include "../Engine/Engine/DataStructures/Pointer/WeakPointer.h"
#include "../Engine/Engine/DataStructures/Pointer/SmartPointer.h"
using json = nlohmann::json;
class GameScene;
//A Gameobject holds basic information about an entity in a scene. Position and name are stored here. 
//Each GameObject holds a list of components.

class GameObject
{
	//ListPointer* components;//List of this objects components
	std::vector<SmartPointer<Component>> components;
	std::map<std::string, SmartPointer<Component>> componentMap;
public:
	GameScene* scene; //What scene is this object in.
	SimpleString* name;//The name of this object
	Vector2 position;//the position of this object in the scene
	float rotation=0.0f;//the rotation of this gameobject in degrees
	void addComponent(Component* newComponent);//Adds the given component to this object
	//void RemoveComponent(GameObject* go);//Removes the given component from this object
	bool enabled = true;//Whether this object recieves or ignores update() from the scene
	void update(UpdateParams* params);//Called with the parent scene's update()
	void draw(UpdateParams* params);//Called with the parent scene's draw()
	Matrix4 ObjectToWorldTransform();
	void Serialize(json& j);
	WeakPointer<Component> getComponent(const std::string& tag);
	GameObject(GameScene* scene);
	~GameObject();
	GameObject(const GameObject &other);
};

