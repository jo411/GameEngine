#include "FixedSizeAllocator.h"

void FixedSizeAllocator::Initialize(size_t i_alignment, size_t i_blockCount, BitArray * i_bitArray)
{
	alignment = i_alignment;
	blockCount = i_blockCount;
	bitArray = i_bitArray;
}
