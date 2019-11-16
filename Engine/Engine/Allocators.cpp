#include "Allocators.h"
#include <windows.h>
#include <iostream>
#include <vector>

Allocators* Allocators::m_pInstance = NULL;

Allocators * Allocators::Instance()
{
	if (!m_pInstance)
	{
		Initialize();
	}
	return m_pInstance;
	
}

MyMalloc * Allocators::GetAllocator(size_t ID)
{
	return allAllocators[ID];
}

MyMalloc * Allocators::GetAllocator()
{
	return internalMemory;
}

size_t Allocators::AddAllocator(size_t size)
{
	MyMalloc* newAllocator = (MyMalloc*)VirtualAlloc(NULL, sizeof(MyMalloc), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	void* heapMemory = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	newAllocator->init(heapMemory, size);	
	allAllocators.push_back(newAllocator);
	return allAllocators.size() - 1;
}

void Allocators::mapAllocator(void * ptr, size_t allocatorID)
{
	mappedAllocators.insert(std::make_pair(ptr, allocatorID));
}

size_t Allocators::getMappedAllocator(void * ptr)
{
	if (mappedAllocators.count(ptr))
	{
		return mappedAllocators.find(ptr)->second;
	}

	return -1;
}


void Allocators::Initialize()
{
	m_pInstance = (Allocators*)VirtualAlloc(NULL, sizeof(Allocators), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	MyMalloc* newAllocator = (MyMalloc*)VirtualAlloc(NULL, sizeof(MyMalloc), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	void* heapMemory = VirtualAlloc(NULL, DEFAULT_HEAP_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	newAllocator->init(heapMemory, DEFAULT_HEAP_SIZE);
	m_pInstance->internalMemory = newAllocator;
}
//
////placement new cannot be replaced in cpp11
//void* operator new(size_t size, void* where)
//{
//	std::cout << "Calling placement new with data at: " << where << "\n";
//	return where;
//}

//New with specified ID
void* operator new(size_t size, size_t allocatorID)
{
	std::cout << "Calling new on allocator: " << allocatorID << ".\n";
	void* ptr = Allocators::Instance()->GetAllocator(allocatorID)->mm_malloc(size);
	Allocators::Instance()->mapAllocator(ptr, allocatorID);
	return ptr;
}

//generic new
void * operator new(size_t size)
{
	std::cout << "Calling new with: " << size << " bytes.\n";
	return Allocators::Instance()->GetAllocator()->mm_malloc(size);
}

//generic delete
void operator delete(void* ptr)
{
	
	size_t allocatorUsed = Allocators::Instance()->getMappedAllocator(ptr);
	if (allocatorUsed >= 0)
	{
		std::cout << "Calling delete on: " << ptr << "in allocator: "<<allocatorUsed<<"\n";
		Allocators::Instance()->GetAllocator(allocatorUsed)->mm_free(ptr);
	}
	else
	{
		std::cout << "Calling delete on: " << ptr << "\n";
		Allocators::Instance()->GetAllocator()->mm_free(ptr);
	}
	
}

//
//void *operator new[](std::size_t s)
//{
//	// TODO: implement
//	return NULL;
//}
//void operator delete[](void *p)
//{
//	// TODO: implement
//}