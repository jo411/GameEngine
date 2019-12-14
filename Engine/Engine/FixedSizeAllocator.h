#pragma once
#include "BitArray.h"
class FixedSizeAllocator
{
public:
	void Initialize(size_t i_alignment, size_t i_blockCount, BitArray* i_bitArray);

private:

	size_t alignment; 
	size_t blockCount;
	BitArray* bitArray;
};

