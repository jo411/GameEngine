#include "FixedSizeAllocator.h"
#include <windows.h>
#include <assert.h>
#include "BitArray.h"
#include <iostream>
void FixedSizeAllocator::Initialize(size_t i_alignment, size_t i_blockCount, BitArray * i_bitArray)
{
	alignment = i_alignment;
	blockCount = i_blockCount;
	m_bitArray = i_bitArray;

	size_t heapsize = blockCount * alignment + (blockCount*2 * sizeof(GuardBand));

	m_heap = VirtualAlloc(NULL, heapsize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	assert(m_heap);
}

void FixedSizeAllocator::Destroy()
{
}

void * FixedSizeAllocator::alloc()
{
	size_t index;		
	if (m_bitArray->GetFirstClearBit(index))
	{
		char* bp = reinterpret_cast<char*>(m_heap)+ (index*blocksize());
		m_bitArray->SetBit(index);
		return payloadPointer(bp);

	}
	else
	{
		return nullptr;//No more blocks
	}
}

void FixedSizeAllocator::free(void * ptr)
{
	size_t index = 0; 
	char* baseBlockPtr = reinterpret_cast<char*>(ptr);
	ptrdiff_t address = baseBlockPtr - reinterpret_cast<char*>(m_heap);
	index = address / blocksize();
	void* base = baseBlockPtr - sizeof(GuardBand);

	bool isAligned = (((uintptr_t)base) % blocksize()==0);//is this pointer aligned within this allocator
	bool isOutstanding = m_bitArray->IsBitSet(index);//this is an outstanding allocation from this allocator

	if (isAligned && isOutstanding)
	{
		m_bitArray->ClearBit(index);
#ifdef _DEBUG//check guardbanding in debug release only to save performance
		GuardBand* gbPtr = firstGuard(ptr);
		GuardBand* lastGbPtr = lastGuard(ptr);
		if (*gbPtr != guardPattern || *lastGbPtr != guardPattern)//Someone mangled the guard
		{
			std::cout << "Broken GuardBand detected. Memory was written out of bounds at address: " << &ptr<<"\n";
		}		
#endif // DEBUG//check guardbanding in debug release only to save performance

		*gbPtr = guardPattern;//reset the guards for next time
		*lastGbPtr = guardPattern;
	}


}

bool FixedSizeAllocator::contains(void * ptr)
{
	return false;
}
