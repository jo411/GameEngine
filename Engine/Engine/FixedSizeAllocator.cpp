#include "FixedSizeAllocator.h"
#include <windows.h>
#include <assert.h>
#include "BitArray.h"
#include <iostream>
#include <stdio.h>
#include <inttypes.h>
void FixedSizeAllocator::Initialize(size_t i_alignment, size_t i_blockCount, BitArray * i_bitArray)
{
	m_alignment = i_alignment;
	m_blockCount = i_blockCount;
	m_bitArray = i_bitArray;

	heapSize = m_blockCount * m_alignment + (m_blockCount*2 * sizeof(GuardBand));

	m_heap = VirtualAlloc(NULL, heapSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	assert(m_heap);
}

void FixedSizeAllocator::Destroy()
{

#ifdef _DEBUG
	size_t index = 0;
	while (m_bitArray->GetFirstSetBit(index))
	{
		char* address = reinterpret_cast<char*>(m_heap) + (index * blocksize());
		void* payload = payloadPointer(address);
		printf("Leaked memory from fixed allocator of size %zu at address: 0x%" PRIXPTR "\n", m_alignment, reinterpret_cast<uintptr_t>(payload));
		m_bitArray->ClearBit(index);
	}
#endif // _DEBUG
		
	VirtualFree(m_heap,heapSize,MEM_RELEASE);//free the heap 
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
	char* basePayloadPtr = reinterpret_cast<char*>(ptr);
	ptrdiff_t addressOffset = basePayloadPtr - reinterpret_cast<char*>(m_heap);
	index = addressOffset / blocksize();
	size_t offset = addressOffset - sizeof(GuardBand);

	bool isAligned = (((uintptr_t)offset) % blocksize()==0);//is this pointer aligned within this allocator
	bool isOutstanding = m_bitArray->IsBitSet(index);//this is an outstanding allocation from this allocator

	if (isAligned && isOutstanding)
	{
		m_bitArray->ClearBit(index);
#ifdef _DEBUG//check guardbanding in debug release only to save performance
		GuardBand* gbPtr = firstGuard(ptr);
		GuardBand* lastGbPtr = lastGuard(ptr);
		if (*gbPtr != guardPattern || *lastGbPtr != guardPattern)//Someone mangled the guard
		{
			printf("Broken GuardBand detected. Memory was written out of bounds at address: 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(ptr));
		}		
#endif // DEBUG//check guardbanding in debug release only to save performance

		*gbPtr = guardPattern;//reset the guards for next time
		*lastGbPtr = guardPattern;

		m_bitArray->ClearBit(index);
	}


}

bool FixedSizeAllocator::contains(void * ptr)
{
	return (ptr >= m_heap && ptr <= reinterpret_cast<char*>(m_heap) + heapSize);
}
