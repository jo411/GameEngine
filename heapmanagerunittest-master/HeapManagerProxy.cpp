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
	return nullptr;
}

void * HeapManagerProxy::alloc(HeapManager * i_pManager, size_t i_size, unsigned int i_alignment)
{
	return nullptr;
}

bool HeapManagerProxy::free(HeapManager * i_pManager, void * i_ptr)
{
	return false;
}

void HeapManagerProxy::Collect(HeapManager * i_pManager)
{
}

bool HeapManagerProxy::Contains(const HeapManager * i_pManager, void * i_ptr)
{
	return false;
}

bool HeapManagerProxy::IsAllocated(const HeapManager * i_pManager, void * i_ptr)
{
	return false;
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
}

void HeapManagerProxy::ShowOutstandingAllocations(const HeapManager * i_pManager)
{
}
