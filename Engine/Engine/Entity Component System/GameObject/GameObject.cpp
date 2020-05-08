#include "GameObject.h"
#include "DataStructures/Pointer/SmartPointer.h"

//Takes a new component and adds it to the internal list for this Object.
//Currently cannot be called during an update like the GameScene addcomponent()
void GameObject::addComponent(Component * newComponent)
{
	SmartPointer<Component> sptr(newComponent);

	sptr->registerGameObject(this);
	//components->add(newComponent);
	components.push_back(sptr);
	sptr->onAddToObject();
	componentMap.insert(std::pair<std::string, SmartPointer<Component>>(sptr->getTag(), sptr));
}

////Remove the given object from the list
//void GameObject::RemoveComponent(GameObject * go)
//{
//	//components.erase(go);
//	//components->remove(go);
//}

//Updates all enabled components on this gameobject 
void GameObject::update(UpdateParams* params)
{
	for (int i = 0; i <components.size(); i++)
	{
		//Component* obj = ((Component*)(components->getAt(i)));
		SmartPointer<Component> obj = components[i];
		if (obj->enabled)
		{
			obj->update(params);
		}
	}
}

//Draws all components on this gameobject
void GameObject::draw(UpdateParams * params)
{
	for (int i = 0; i < components.size(); i++)
	{
		SmartPointer<Component> obj = components[i];
		if (obj->enabled)
		{
			obj->draw(params);
		}
	}
}

Matrix4 GameObject::ObjectToWorldTransform()
{
	Matrix4 transform = Matrix4::createRotationZ(rotation);
	transform = Matrix4::createTranslation(position.getX(), position.getY(), 0)* transform;
	return transform;
}

void GameObject::Serialize(json & j)
{
	j["Name"] = name->getCharArray();
	j["Position"] = { {"x",position.getX()},{"y",position.getY()} };
	for (int i = 0; i <components.size(); i++)
	{
		SmartPointer<Component> obj = components[i];
		obj->Serialize(j);		
	}
}

WeakPointer<Component> GameObject::getComponent(const std::string & tag)
{
	if (componentMap.count(tag))
	{
		return WeakPointer<Component>(componentMap.at(tag));
	}
	return WeakPointer<Component>();
}

GameObject::GameObject(GameScene* scene)
{
	//Start at (0,0)
	position.x=0;
	position.y = 0;

	//components = new ListPointer(0);//Creates a list of component pointers (type 0)
	name = new SimpleString();	
	this->scene = scene;
}
//removes dynamic memory 
GameObject::~GameObject()
{
	componentMap.clear();
	components.clear();
	//delete components;
	delete name;
}

GameObject::GameObject(const GameObject & other)
{
	//Start at (0,0)
	position.x = 0;
	position.y = 0;

	//components = new ListPointer(0);//Creates a list of component pointers (type 0)
	name = new SimpleString(*other.name);	
	this->scene = other.scene;
}
