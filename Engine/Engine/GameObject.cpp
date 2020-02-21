#include "GameObject.h"

//Takes a new component and adds it to the internal list for this Object.
//Currently cannot be called during an update like the GameScene addcomponent()
void GameObject::addComponent(Component * newComponent)
{
	newComponent->registerGameObject(this);
	components->add(newComponent);
	newComponent->onAddToObject();
}

//Remove the given object from the list
void GameObject::RemoveComponent(GameObject * go)
{
	components->remove(go);
}

//Updates all enabled components on this gameobject 
void GameObject::update(UpdateParams* params)
{
	for (int i = 0; i <= components->count(); i++)
	{
		Component* obj = ((Component*)(components->getAt(i)));
		if (obj->enabled)
		{
			obj->update(params);
		}
	}
}

//Draws all components on this gameobject
void GameObject::draw(UpdateParams * params)
{
	for (int i = 0; i <= components->count(); i++)
	{
		Component* obj = ((Component*)(components->getAt(i)));
		if (obj->enabled)
		{
			obj->draw(params);
		}
	}
}

void GameObject::Serialize(json & j)
{
	j["Name"] = name->getCharArray();
	j["Position"] = { {"x",position.getX()},{"y",position.getY()} };
	for (int i = 0; i <= components->count(); i++)
	{
		Component* obj = ((Component*)(components->getAt(i)));
		obj->Serialize(j);		
	}
}

GameObject::GameObject(GameScene* scene)
{
	//Start at (0,0)
	position.x=0;
	position.y = 0;

	components = new ListPointer(0);//Creates a list of component pointers (type 0)
	name = new SimpleString();
	this->scene = scene;
}
//removes dynamic memory 
GameObject::~GameObject()
{
	delete components;
	delete name;
}

GameObject::GameObject(const GameObject & other)
{
	//Start at (0,0)
	position.x = 0;
	position.y = 0;

	components = new ListPointer(0);//Creates a list of component pointers (type 0)
	name = new SimpleString(*other.name);	
	this->scene = other.scene;
}
