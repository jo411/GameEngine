#include "CombinedAllocators.h"
#include <malloc.h>
#include <windows.h>

CombinedAllocators* CombinedAllocators::m_instance = NULL;

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
