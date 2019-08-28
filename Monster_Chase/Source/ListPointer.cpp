#include "ListPointer.h"
#include "malloc.h"



void ListPointer::grow()
{
	objectCount += GROWTH_COUNT;
	objects = (void**)realloc(objects, sizeof(void*)*objectCount);

	for (int i = objectPointer; i < objectCount; i++)
	{
		objects[i] = nullptr;
	}
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
			free(objects[i]);
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

ListPointer::ListPointer()
{
	objects = (void**)malloc(sizeof(void*));
	objects[0] = nullptr;
	objectPointer = 0;
	objectCount = 1;
}


ListPointer::~ListPointer()
{
	for (int i = 0; i < objectCount; i++)
	{
		delete objects[i];
	}

	free(objects);
}
