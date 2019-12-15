#pragma once
#include "FixedSizeAllocator.h"
#include "MyMalloc.h"
class CombinedAllocators
{
public: 
	static CombinedAllocators* Instance();//Access to singleton instance

	void Init(void * i_pHeapMemory, size_t i_sizeHeapMemory);
	void Destroy();
	void* m_alloc(size_t size);
	void m_free(void* ptr);	
private:
	static CombinedAllocators* m_instance;

	CombinedAllocators() {};  // Private so that it can  not be called
	CombinedAllocators(CombinedAllocators const&) {};             // copy constructor is private
	CombinedAllocators& operator=(CombinedAllocators const&) {};  // assignment operator is private


	FixedSizeAllocator* Size16Allocator;
	static size_t num16ByteBlocks;
	FixedSizeAllocator* Size32Allocator;
	static size_t num32ByteBlocks;
	FixedSizeAllocator* Size96Allocator;
	static size_t num96ByteBlocks;

	MyMalloc* defaultHeap;
};

