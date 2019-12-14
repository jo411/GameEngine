#include "MemorySystem.h"
#include "Engine/CombinedAllocators.h"


bool InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	CombinedAllocators::Instance()->Init(i_pHeapMemory, i_sizeHeapMemory);


	// create your HeapManager and FixedSizeAllocators
	return true;
}

void Collect()
{
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	CombinedAllocators::Instance()->Destroy();
	// Destroy your HeapManager and FixedSizeAllocators
}

