#pragma once
#include <new>
#include <vector>
#include <map>
#include "MyMalloc.h"
#include <string>
class Allocators
{

	
public:
	static const size_t DEFAULT_HEAP_SIZE = 1024*8;//reserve 8 kb for the default heap
	static std::string DEFAULT_ALLOCATOR;
	static Allocators* Instance();
	MyMalloc* GetAllocator(int ID);
	MyMalloc* GetAllocator();
	int AddAllocator(size_t size=DEFAULT_HEAP_SIZE);		
	void mapAllocator(void* ptr, int allocatorID);
	void unmapAllocator(void* ptr);
	int getMappedAllocator(void* ptr);
private:
	static std::vector<MyMalloc*> allAllocators;	
	static std::map<void*, int> mappedAllocators;
	static void Initialize();
	Allocators() {};// Private so that it can  not be called	
	Allocators(Allocators const&) {};// copy constructor is private
	Allocators& operator=(Allocators const&) {};// assignment operator is private
	static Allocators* m_pInstance;
	MyMalloc* internalMemory =nullptr;

	
};

void* operator new(size_t size, int allocatorID);
void operator delete(void* ptr, int allocatorID);
void* operator new(size_t size);
void operator delete(void* ptr);
void* operator new[](std::size_t s);
void operator delete[](void* p);