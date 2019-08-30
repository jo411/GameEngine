#include "ListPointer.h"
#include "malloc.h"
#include "Component.h"
#include "GameObject.h"
#include <iostream>

//Reallocates this list when it needs more room for elements
void ListPointer::grow()
{
	objectCount += GROWTH_COUNT;//increase the list size by GROWTH_COUNT
	objects = (void**)realloc(objects, sizeof(void*)*objectCount);//reallocate the list with the larger size

	for (int i = objectPointer; i < objectCount; i++)//null out any new elements in the array. Just to be safe
	{
		objects[i] = nullptr;
	}
}

//Removes the specified pointer, if present, from this list and frees its memory
void ListPointer::deletePointer(void * ptr)
{
	if (pointerType == 0)//faux generics since delete is type specific
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

//How many elements are in this list
int ListPointer::count()
{
	return objectPointer - 1;
}

//Adds the specified pointer to the list at the location pointed to by objectPointer 
//THIS POINTER MUST BE ALLOCATED WITH NEW
void ListPointer::add(void* pntr)
{	
	objects[objectPointer] = pntr;
	objectPointer++;//update the pointer to the next open element
	if (objectPointer >= objectCount)//if the new element filled the list grow the array
	{
		grow();
	}
	
}

//Removes a pointer from this list and swaps the last element in the list to its location to avoid fragmentation
void ListPointer::remove(void * obj)
{
	for (int i = 0; i < objectCount; i++)//search for the pointer
	{
		if (objects[i] == obj)
		{				
			deletePointer(objects[i]);//call the delete helper
			objects[i] = objects[objectPointer - 1];//swap position with the last element in the list so that there are never fragmented sections
			objects[objectPointer - 1] = nullptr;
			objectPointer--;//move the pointer back
			break;
		}
	}
}

//Gets the pointer at index if possible
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

//Constructor starts with a list of one, empty, element
ListPointer::ListPointer(int type)
{
	this->pointerType = type;
	objects = (void**)malloc(sizeof(void*));
	objects[0] = nullptr;
	objectPointer = 0;
	objectCount = 1;
}

//Destructor frees all the memory in the list and the itself
ListPointer::~ListPointer()
{
	for (int i = 0; i < objectCount; i++)
	{
		deletePointer(objects[i]);
	}

	free(objects);
}
