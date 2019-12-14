#include "BitArray.h"
#include "MyMalloc.h"
#include <intrin.h>
#include<new>

BitArray * BitArray::Create(size_t numBits, MyMalloc * heapManager)
{
	void* tmpPtr = heapManager->mm_malloc(sizeof(BitArray));
		
	BitArray* newBitArray = new (tmpPtr) BitArray(numBits, heapManager);

	return newBitArray;
}

BitArray::BitArray(size_t numBits, MyMalloc * i_heapManager)
{
	bitCount = numBits;
	heapManager = i_heapManager;

	allignedWordCount = (size_t)ceil((double)numBits / WordSizeInBits());
	
	

	bits = static_cast<size_t*>(heapManager->mm_malloc(allignedWordCount * sizeof(size_t)));
	
	ClearAll();

	size_t index = 65;
	SetBit(index);
	ClearBit(index);
	SetBit(66);
	if (IsBitSet(66))
	{
		heapManager = nullptr;
	}
	else
	{
		heapManager = nullptr;
	}


}

BitArray::~BitArray()
{
}

void BitArray::ClearAll()
{
	for (unsigned int i = 0; i < allignedWordCount; i++)
	{
		bits[i] = 0;
	}
}

void BitArray::SetAll()
{
	for (unsigned int i = 0; i < allignedWordCount; i++)
	{
		bits[i] = SIZE_MAX;
	}
}

inline bool BitArray::IsBitSet(size_t index) const
{
	size_t wordIndex = getWordIndex(index);
	size_t leftover = index - (wordIndex * WordSizeInBits());
	return (bits[wordIndex] >> leftover) & 1ULL;
	
}

inline bool BitArray::isBitClear(size_t index) const
{
	return !IsBitSet(index);
}

void BitArray::SetBit(size_t index)
{
	size_t wordIndex = getWordIndex(index);
	size_t leftover = index - (wordIndex * WordSizeInBits());
	bits[wordIndex] |= 1ULL << leftover;
}

void BitArray::ClearBit(size_t index)
{
	size_t wordIndex = getWordIndex(index);
	size_t leftover = index - (wordIndex * WordSizeInBits());
	bits[wordIndex] &= ~(1ULL << leftover);
}

bool BitArray::GetFirstClearBit(size_t & index) const
{
	return false;
}

bool BitArray::GetFirstSetBit(size_t & index) const
{
	return false;
}

bool BitArray::operator[](size_t index) const
{
	return false;
}

bool BitArray::isValid(size_t index)
{
	return (index >= 0 && index < bitCount);
}
