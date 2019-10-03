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
