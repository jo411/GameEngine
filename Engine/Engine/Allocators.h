#pragma once
#include <new>
#include <map>
#include "MyMalloc.h"
class Allocators
{

	typedef std::map<std::string, MyMalloc*> AllocatorMap;
	typedef std::pair<std::string, MyMalloc*> AllocatorPair;
public:
	static const size_t DEFAULT_HEAP_SIZE = 4096;
	static const std::string DEFAULT_ALLOCATOR;
	static Allocators* Instance();
	MyMalloc* GetAllocator(std::string key);
	MyMalloc* AddAllocator(std::string key, size_t size=DEFAULT_HEAP_SIZE);	
	
private:
	static void Initialize();
	Allocators() {};// Private so that it can  not be called
	Allocators(Allocators const&) {};// copy constructor is private
	Allocators& operator=(Allocators const&) {};// assignment operator is private
	static Allocators* m_pInstance;
	static MyMalloc* internalManager;
};

