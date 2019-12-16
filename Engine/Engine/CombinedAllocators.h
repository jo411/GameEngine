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

	//As this is a singleton that exists for the life of the program we do not want copying to occur at all

	CombinedAllocators() {};  // Private so that it can  not be called. Only one instance should be created through the Instance() function
	CombinedAllocators(CombinedAllocators const&) {};             // copy constructor is private
	CombinedAllocators& operator=(CombinedAllocators const&) {};  // assignment operator is private


	//TODO: next step is to store these in a dictionary or array for better dynamic changes
	FixedSizeAllocator* Size16Allocator;
	static size_t num16ByteBlocks;
	FixedSizeAllocator* Size32Allocator;
	static size_t num32ByteBlocks;
	FixedSizeAllocator* Size96Allocator;
	static size_t num96ByteBlocks;

	MyMalloc* defaultHeap;
};

