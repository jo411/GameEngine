#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>
#include "Engine/CombinedAllocators.h"

void * __cdecl malloc(size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	
	printf("malloc %zu\n", i_size);

	return CombinedAllocators::Instance()->m_alloc(i_size);
}

void __cdecl free(void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));

	CombinedAllocators::Instance()->m_free(i_ptr);
}

void * operator new(size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("new %zu\n", i_size);


	return CombinedAllocators::Instance()->m_alloc(i_size);
}

void operator delete(void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));

	CombinedAllocators::Instance()->m_free(i_ptr);
}

void * operator new[](size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("new [] %zu\n", i_size);


	return CombinedAllocators::Instance()->m_alloc(i_size);
}

void operator delete [](void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));

	CombinedAllocators::Instance()->m_free(i_ptr);
}