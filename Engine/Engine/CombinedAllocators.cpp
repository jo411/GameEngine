#include "CombinedAllocators.h"
#include <windows.h>
#include "BitArray.h"
#include <new>

CombinedAllocators* CombinedAllocators::m_instance = NULL;
size_t CombinedAllocators::num16ByteBlocks = 100;
size_t CombinedAllocators::num32ByteBlocks = 200;
size_t CombinedAllocators::num96ByteBlocks = 400;

CombinedAllocators* CombinedAllocators::Instance()
{
	if (!m_instance)
	{
		m_instance = (CombinedAllocators*)VirtualAlloc(NULL, sizeof(CombinedAllocators), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	}
	return m_instance;
}



void CombinedAllocators::Init(void * i_pHeapMemory, size_t i_sizeHeapMemory)
{
	defaultHeap = (MyMalloc*)VirtualAlloc(NULL, sizeof(MyMalloc), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	defaultHeap->init(i_pHeapMemory, i_sizeHeapMemory);

	Size16Allocator = static_cast<FixedSizeAllocator*>(defaultHeap->mm_malloc(sizeof(FixedSizeAllocator)));

	Size16Allocator->Initialize(16, this->num16ByteBlocks, BitArray::Create(this->num16ByteBlocks, defaultHeap));

	
	
}

void CombinedAllocators::Destroy()
{
	char* ptr = (char*)Size16Allocator->alloc();
	char* ptr2 = (char*)Size16Allocator->alloc();
	char* ptr3 = (char*)Size16Allocator->alloc();

	Size16Allocator->free(ptr);
	//Size16Allocator->free(ptr2);
	Size16Allocator->free(ptr3);

	Size16Allocator->Destroy();
	ptr3 = nullptr;
}

void * CombinedAllocators::m_alloc(size_t size)
{
	return defaultHeap->mm_malloc(size);
}

void CombinedAllocators::m_free(void * ptr)
{
	defaultHeap->mm_free(ptr);
}
