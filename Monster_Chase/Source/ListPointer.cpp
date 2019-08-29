#include "ListPointer.h"
#include "malloc.h"
#include "Component.h"
#include "GameObject.h"
#include <iostream>


void ListPointer::grow()
{
	objectCount += GROWTH_COUNT;
	objects = (void**)realloc(objects, sizeof(void*)*objectCount);

	for (int i = objectPointer; i < objectCount; i++)
	{
		objects[i] = nullptr;
	}
}

void ListPointer::deletePointer(void * ptr)
{
	if (pointerType == 0)
	{
		delete (Component*)(ptr);
	}
	else
	{
		delete (GameObject*)(ptr);
	}
}

//clear the list WITHOUT freeing any memory
void ListPointer::clearNonDestructive()
{
	for (int i = 0; i < objectCount; i++)
	{
		objects[i] = nullptr;
	}
	objectPointer = 0;

}

int ListPointer::count()
{
	return objectPointer - 1;
}

void ListPointer::add(void* pntr)
{	
	objects[objectPointer] = pntr;
	objectPointer++;
	if (objectPointer >= objectCount)
	{
		grow();
	}
	
}

void ListPointer::remove(void * obj)
{
	for (int i = 0; i < objectCount; i++)
	{
		if (objects[i] == obj)
		{				
			deletePointer(objects[i]);
			objects[i] = objects[objectPointer - 1];
			objects[objectPointer - 1] = nullptr;
			objectPointer--;
			break;
		}
	}
}

void * ListPointer::getAt(int index)
{
	
	if (index < objectPointer)
	{
		return objects[index];
	}
	else
	{
		return nullptr;
	}
}

ListPointer::ListPointer(int type)
{
	this->pointerType = type;
	objects = (void**)malloc(sizeof(void*));
	objects[0] = nullptr;
	objectPointer = 0;
	objectCount = 1;
}


ListPointer::~ListPointer()
{
	for (int i = 0; i < objectCount; i++)
	{
		deletePointer(objects[i]);
	}

	free(objects);
}
