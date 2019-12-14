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

	char* ptr = (char*)Size16Allocator->alloc();
	ptr -= sizeof(char);
	*ptr = 0xf3;
	//ptr += sizeof(char);
	Size16Allocator->free(ptr);
	char* ptr2 = (char*)Size16Allocator->alloc();
}
//BitArray* newBitArray = new (tmpPtr) BitArray(numBits, heapManager);

void CombinedAllocators::Destroy()
{

}

void * CombinedAllocators::m_alloc(size_t size)
{
	return defaultHeap->mm_malloc(size);
}

void CombinedAllocators::m_free(void * ptr)
{
	defaultHeap->mm_free(ptr);
}
