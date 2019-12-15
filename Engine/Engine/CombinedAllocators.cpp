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
	//TODO:: Should probably make these allocators dynamically sized for different setups?
	defaultHeap = static_cast<MyMalloc*>(VirtualAlloc(NULL, sizeof(MyMalloc), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	defaultHeap->init(i_pHeapMemory, i_sizeHeapMemory);

	Size16Allocator = static_cast<FixedSizeAllocator*>(VirtualAlloc(NULL, sizeof(FixedSizeAllocator), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	Size16Allocator->Initialize(16, this->num16ByteBlocks, BitArray::Create(this->num16ByteBlocks, defaultHeap));

	Size32Allocator = static_cast<FixedSizeAllocator*>(VirtualAlloc(NULL, sizeof(FixedSizeAllocator), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	Size32Allocator->Initialize(32, this->num32ByteBlocks, BitArray::Create(this->num32ByteBlocks, defaultHeap));

	Size96Allocator = static_cast<FixedSizeAllocator*>(VirtualAlloc(NULL, sizeof(FixedSizeAllocator), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	Size96Allocator->Initialize(96, this->num96ByteBlocks, BitArray::Create(this->num96ByteBlocks, defaultHeap));

}

void CombinedAllocators::Destroy()
{
	Size16Allocator->Destroy();
	Size32Allocator->Destroy();
	Size96Allocator->Destroy();

	VirtualFree(Size16Allocator, sizeof(FixedSizeAllocator), MEM_RELEASE);
	VirtualFree(Size32Allocator, sizeof(FixedSizeAllocator), MEM_RELEASE);
	VirtualFree(Size96Allocator, sizeof(FixedSizeAllocator), MEM_RELEASE);


	VirtualFree(defaultHeap, sizeof(MyMalloc), MEM_RELEASE);
	VirtualFree(m_instance, sizeof(CombinedAllocators), MEM_RELEASE);
}

void * CombinedAllocators::m_alloc(size_t size)
{
	return defaultHeap->mm_malloc(size);
}

void CombinedAllocators::m_free(void * ptr)
{
	defaultHeap->mm_free(ptr);
}

