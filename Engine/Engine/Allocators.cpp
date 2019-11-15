#include "Allocators.h"
#include <windows.h>

Allocators * Allocators::Instance()
{
	if (!m_pInstance)
	{
		Initialize();
	}
	return m_pInstance;
}

MyMalloc * Allocators::GetAllocator(std::string key)
{
	return nullptr;
}

MyMalloc * Allocators::AddAllocator(std::string key, size_t size)
{
	return nullptr;
}

void Allocators::Initialize()
{
	internalManager = (MyMalloc*)VirtualAlloc(NULL, sizeof(MyMalloc), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	
}
