#include "Allocators.h"
#include <windows.h>
#include <iostream>
#include <vector>

Allocators* Allocators::m_pInstance = NULL;
std::map<void*, int> Allocators::mappedAllocators = std::map<void*, int>();
std::vector<MyMalloc*> Allocators::allAllocators = std::vector<MyMalloc*>();
#define TRACING_ENABLED

Allocators * Allocators::Instance()
{
	if (!m_pInstance)
	{
		Initialize();
	}
	return m_pInstance;
	
}

MyMalloc * Allocators::GetAllocator(int ID)
{
	return allAllocators[ID];
}

MyMalloc * Allocators::GetAllocator()
{
	return internalMemory;
}

int Allocators::AddAllocator(size_t size)
{
	MyMalloc* newAllocator = (MyMalloc*)VirtualAlloc(NULL, sizeof(MyMalloc), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	void* heapMemory = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	newAllocator->init(heapMemory, size);	
	allAllocators.push_back(newAllocator);
	return (int)(allAllocators.size() - 1);
}

void Allocators::mapAllocator(void * ptr, int allocatorID)
{
	mappedAllocators.insert(std::make_pair(ptr, allocatorID));
}
void Allocators::unmapAllocator(void* ptr)
{
	mappedAllocators.erase(ptr);
}

int Allocators::getMappedAllocator(void * ptr)
{
	std::map<void*, int>::iterator it = mappedAllocators.find(ptr);
	
	if (it != mappedAllocators.end())
	{
		//element found;
		return it->second;
	}
	return -1;
}


void Allocators::Initialize()
{
	m_pInstance = (Allocators*)VirtualAlloc(NULL, sizeof(Allocators), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	MyMalloc* newAllocator = (MyMalloc*)VirtualAlloc(NULL, sizeof(MyMalloc), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	void* heapMemory = VirtualAlloc(NULL, DEFAULT_HEAP_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	newAllocator->init(heapMemory, DEFAULT_HEAP_SIZE);
	if (m_pInstance != nullptr)
	{
		m_pInstance->internalMemory = newAllocator;			
	}
	
}
//
////placement new cannot be replaced in cpp11
//void* operator new(size_t size, void* where)
//{
//	std::cout << "Calling placement new with data at: " << where << "\n";
//	return where;
//}

//New with specified ID
//I want to use a size_t instead of an int
//I have no idea why this is needed but without using an int in place of size_t the function was treated as simply a placement delete and would not compile. 
void* operator new(size_t size, int allocatorID)
{
#ifdef TRACING_ENABLED
	std::cout << "Calling new on allocator: " << allocatorID << " with " << size << " bytes.\n";
#endif // TRACING_ENABLED
	
	void* ptr = Allocators::Instance()->GetAllocator(allocatorID)->mm_malloc(size);
	Allocators::Instance()->mapAllocator(ptr, allocatorID);
	return ptr;
}
void operator delete(void* ptr, int allocatorID)
{

}
//generic new
void * operator new(size_t size)
{
#ifdef TRACING_ENABLED
	std::cout << "Calling new on default allocator with: " << size << " bytes.\n";
#endif // TRACING_ENABLED
	
	return Allocators::Instance()->GetAllocator()->mm_malloc(size);
}

//generic delete
void operator delete(void* ptr)
{
	
	int allocatorUsed = Allocators::Instance()->getMappedAllocator(ptr);
	if (allocatorUsed >= 0)
	{
#ifdef TRACING_ENABLED
		std::cout << "Calling delete on: " << ptr << " in allocator: " << allocatorUsed << "\n";
#endif // TRACING_ENABLED
		
		Allocators::Instance()->unmapAllocator(ptr);
		Allocators::Instance()->GetAllocator(allocatorUsed)->mm_free(ptr);
		
	}
	else
	{
#ifdef TRACING_ENABLED
		std::cout << "Calling delete on: " << ptr << " in default allocator\n";
#endif // TRACING_ENABLED
		
		Allocators::Instance()->GetAllocator()->mm_free(ptr);
	}
	
}


void* operator new[](std::size_t size)
{
#ifdef TRACING_ENABLED
	std::cout << "Calling new[] with size "<<size<<"\n";
#endif // TRACING_ENABLED
	void* ptr = Allocators::Instance()->GetAllocator()->mm_malloc(size+sizeof(size_t));//get enough room for the number of objects
	char* tmp = reinterpret_cast<char*>(ptr);
	*tmp = size;//mark the size
	return ptr;
}
void operator delete[](void* p)
{
#ifdef TRACING_ENABLED
	std::cout << "Calling delete[] on"<<p<<"\n";
#endif // TRACING_ENABLED
	// TODO: implement
}