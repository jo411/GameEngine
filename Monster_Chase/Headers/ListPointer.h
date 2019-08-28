#pragma once
class ListPointer
{

	const int DEFAULT_OBJECT_COUNT = 10;
	const int GROWTH_COUNT = 10;
	int objectCount = 0;
	int objectPointer = -1;	
	void** objects;
	void grow();
public:
	int count();
	void add(void* pntr);
	void remove(void* obj);
	void* getAt(int index);
	ListPointer();
	~ListPointer();
};

