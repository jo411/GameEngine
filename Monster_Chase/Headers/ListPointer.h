#pragma once
class ListPointer
{

	const int DEFAULT_OBJECT_COUNT = 10;
	const int GROWTH_COUNT = 10;
	int objectCount = 0;
	int objectPointer = -1;	
	void** objects;
	void grow();
	int pointerType = -1;//what kind of pointer does this list store. 0>GameObject 1>Component  I hate this but no option for generics without std
	void deletePointer(void* ptr);
public:
	int count();
	void add(void* pntr);
	void remove(void* obj);
	void* getAt(int index);
	void clearNonDestructive();
	ListPointer(int type);
	~ListPointer();
};

