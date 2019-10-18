#include "Externals/HeapManagerProxy.h"
#include <windows.h>

HeapManager * HeapManagerProxy::CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	MyMalloc* managerPointer = (MyMalloc*)VirtualAlloc(NULL, sizeof(MyMalloc), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	managerPointer->init(i_pMemory,i_sizeMemory);
	return (HeapManager*)managerPointer;//TODO: return what is this right?
}

void HeapManagerProxy::Destroy(HeapManager * i_pManager)
{
	VirtualFree(i_pManager,0,MEM_RELEASE);
}

void * HeapManagerProxy::alloc(HeapManager * i_pManager, size_t i_size)
{
 	return ((MyMalloc*)(i_pManager))->mm_malloc(i_size);
}

void * HeapManagerProxy::alloc(HeapManager * i_pManager, size_t i_size, unsigned int i_alignment)
{
	return nullptr;
}

bool HeapManagerProxy::free(HeapManager * i_pManager, void * i_ptr)
{
	return ((MyMalloc*)(i_pManager))->mm_free(i_ptr);
	
}

void HeapManagerProxy::Collect(HeapManager * i_pManager)
{
	return;//Coalescing is done when freeing happens
}

bool HeapManagerProxy::Contains(const HeapManager * i_pManager, void * i_ptr)
{
	return true;
}

bool HeapManagerProxy::IsAllocated(const HeapManager * i_pManager, void * i_ptr)
{
	return true;
}

size_t HeapManagerProxy::GetLargestFreeBlock(const HeapManager * i_pManager)
{
	return size_t();
}

size_t HeapManagerProxy::GetTotalFreeMemory(const HeapManager * i_pManager)
{
	return size_t();
}

void HeapManagerProxy::ShowFreeBlocks(const HeapManager * i_pManager)
{
	((MyMalloc*)(i_pManager))->printFreeList();
}

void HeapManagerProxy::ShowOutstandingAllocations(const HeapManager * i_pManager)
{
	((MyMalloc*)(i_pManager))->printMemory();
}
