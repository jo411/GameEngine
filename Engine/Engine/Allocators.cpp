#include "Allocators.h"
#include <windows.h>
#include <iostream>
#include <vector>

Allocators* Allocators::m_pInstance = NULL;
std::string	Allocators::DEFAULT_ALLOCATOR = std::string("Default");
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


void Allocators::Initialize()
{
	m_pInstance = (Allocators*)VirtualAlloc(NULL, sizeof(Allocators), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	MyMalloc* newAllocator = (MyMalloc*)VirtualAlloc(NULL, sizeof(MyMalloc), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	void* heapMemory = VirtualAlloc(NULL, DEFAULT_HEAP_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	newAllocator->init(heapMemory, DEFAULT_HEAP_SIZE);
	m_pInstance->internalMemory = newAllocator;
}



void * operator new(size_t size)
{
	std::cout << "Calling new with: " << size << " bytes.\n";
	return Allocators::Instance()->GetAllocator()->mm_malloc(size);
}

void operator delete(void* ptr)
{
	std::cout << "Calling delete on: " << ptr << "\n";
	Allocators::Instance()->GetAllocator()->mm_free(ptr);
}

void *operator new[](std::size_t s)
{
	// TODO: implement
	return NULL;
}
void operator delete[](void *p)
{
	// TODO: implement
}