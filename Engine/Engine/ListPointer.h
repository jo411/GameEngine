#pragma once
//The List<pointer> is simply a (semi)generic list that can hold pointers. It manages the memory needed.
class ListPointer
{

	const int DEFAULT_OBJECT_COUNT = 10;//How many objects this list will hold by default
	const int GROWTH_COUNT = 10;//How many objects to add when this list needs to grow.
	int objectCount = 0;//How many objects this list can currently hold at max capacity
	int objectPointer = -1;	//Index to the next open index in the list
	void** objects; //Pointer array (Where all the data for this list is stored
	bool grow(); //Reallocates this list when it needs more room for elements
	int pointerType = -1;//What kind of pointer does this list store. 0>GameObject 1>Component (I hate this but no option for generics without std)
	void deletePointer(void* ptr);//Removes the specified pointer, if present, from this list and frees its memory
public:
	int count();//How many elements are in this list
	void add(void* pntr);//Adds the specified pointer to the list at the location pointed to by objectPointer 
	void remove(void* obj);//Helper function - Removes a pointer from this list and swaps the last element in the list to its location to avoid fragmentation
	void* getAt(int index);//Gets the pointer at index if possible
	void clearNonDestructive();//Clears this list without freeing any memory
	ListPointer(int type);
	~ListPointer();
};

