#include "CombinedAllocators.h"
#include <malloc.h>

CombinedAllocators* CombinedAllocators::m_instance = NULL;

void CombinedAllocators::Init(void * i_pHeapMemory, size_t i_sizeHeapMemory)
{

}

void CombinedAllocators::Destroy()
{
}

void * CombinedAllocators::m_alloc(size_t size)
{
	return nullptr;
}

void CombinedAllocators::m_free(void * ptr)
{
}
