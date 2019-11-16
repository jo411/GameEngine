#pragma once
#include <new>
#include <vector>
#include <map>
#include "MyMalloc.h"
class Allocators
{

	
public:
	static const size_t DEFAULT_HEAP_SIZE = 1024*8;//reserve 8 kb for the default heap
	static std::string DEFAULT_ALLOCATOR;
	static Allocators* Instance();
	MyMalloc* GetAllocator(size_t ID);
	MyMalloc* GetAllocator();
	size_t AddAllocator(size_t size=DEFAULT_HEAP_SIZE);		
	void mapAllocator(void* ptr, size_t allocatorID);
	size_t getMappedAllocator(void* ptr);
private:
	std::vector<MyMalloc*> allAllocators;	
	std::map<void*, size_t> mappedAllocators;
	static void Initialize();
	Allocators() {};// Private so that it can  not be called
	Allocators(Allocators const&) {};// copy constructor is private
	Allocators& operator=(Allocators const&) {};// assignment operator is private
	static Allocators* m_pInstance;
	MyMalloc* internalMemory;
};

