#include "BitArray.h"
#include <Windows.h>
#include <intrin.h>
#include<new>

BitArray * BitArray::Create(size_t numBits)
{
	void* tmpPtr = VirtualAlloc(NULL, sizeof(BitArray), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		
	BitArray* newBitArray = new (tmpPtr) BitArray(numBits);	
	return newBitArray;
}

BitArray::BitArray(size_t numBits)
{
	bitCount = numBits;

	allignedWordCount = (size_t)ceil((double)numBits / WordSizeInBits());
	size_t arraySize = allignedWordCount * sizeof(size_t);
	bits = static_cast<size_t*>(VirtualAlloc(NULL, arraySize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	ClearAll();	
}

BitArray::~BitArray()
{
	VirtualFree(bits, allignedWordCount * sizeof(size_t), MEM_RELEASE);
	VirtualFree(this, sizeof(BitArray), MEM_RELEASE);
}

BitArray & BitArray::operator=(const BitArray& bitarr)
{
	if (this == &bitarr)
	{
		return *this;
	}

	if (bits)
	{
		VirtualFree(bits, allignedWordCount * sizeof(size_t), MEM_RELEASE);
	}

	bitCount = bitarr.getBitCount();
	allignedWordCount = (size_t)ceil((double)bitCount / WordSizeInBits());
	bits = bitarr.bits;

	return *this;
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



bool BitArray::IsBitSet(size_t index) const
{
	size_t wordIndex = getWordIndex(index);
	size_t leftover = index - (wordIndex * WordSizeInBits());
	return (bits[wordIndex] >> leftover) & 1ULL;
	
}

bool BitArray::IsBitClear(size_t index) const
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
	unsigned long indexUL = 0;
	bool isNonZero = false;
	unsigned int i = 0;
	for (i = 0; i < allignedWordCount; i++)
	{
		if (WordSizeInBits() == 32)
		{
			isNonZero = _BitScanForward(&indexUL, (unsigned long)~bits[i]);
			if (isNonZero)
			{
				i++;//account for the decrement
				break;
			}
		}
		else
		{
#ifdef _WIN64
			isNonZero = _BitScanForward64(&indexUL, ~bits[i]);
#endif
			if (isNonZero)
			{
				i++;//account for the decrement
				break;
			}
		}
	}
	i--;
	index = i * WordSizeInBits() + indexUL;

	if (isValidIndex(index) && isNonZero)
	{
		return true;
	}
	return false;
}

bool BitArray::GetFirstSetBit(size_t & index) const
{	
	unsigned long indexUL=0;
	bool isNonZero=false;
	unsigned int i = 0;	
	for (i = 0; i < allignedWordCount; i++)
	{
		if (WordSizeInBits() == 32)
		{
			isNonZero = _BitScanForward(&indexUL, (unsigned long)bits[i]);
			if (isNonZero)
			{
				i++;//account for the decrement
				break;				
			}
		}
		else
		{
#ifdef _WIN64
			isNonZero = _BitScanForward64(&indexUL, bits[i]);
#endif
			if (isNonZero)
			{
				i++;//account for the decrement
				break;
			}
		}
	}	
	i--;
	index = i*WordSizeInBits() + indexUL;

	if (isValidIndex(index) && isNonZero)
	{
		return true;
	}
	return false;
}

bool BitArray::operator[](size_t index) const
{
	return IsBitSet(index);
}

bool BitArray::isValidIndex(size_t index) const
{
	return (index >= 0 && index < bitCount);
}
