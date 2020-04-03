#include "GameObject.h"
#include "SmartPointer.h"

//Takes a new component and adds it to the internal list for this Object.
//Currently cannot be called during an update like the GameScene addcomponent()
void GameObject::addComponent(Component * newComponent)
{
	SmartPointer<Component> sptr(newComponent);

	newComponent->registerGameObject(this);
	components->add(newComponent);
	newComponent->onAddToObject();	
	componentMap.insert(std::pair<std::string, SmartPointer<Component>>(newComponent->getTag(), sptr));
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

Matrix4 GameObject::WorldToObjectTransform()
{
	Matrix4 transform = Matrix4::createRotationZ(rotation);
	transform = Matrix4::createTranslation(position.getX(), position.getY(), 0)* transform;
	return transform;
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

	components = new ListPointer(0);//Creates a list of component pointers (type 0)
	name = new SimpleString();	
	this->scene = scene;
}
//removes dynamic memory 
GameObject::~GameObject()
{
	componentMap.clear();
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
