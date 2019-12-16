Josh Nelson Final Readme

I did the final inside my Engine as I felt this code fit there and in the future I want to hook up monster chase to the new allocator. 
So there are a lot of extra files in the solution and I hope that isn't a problem. Below are the files that are used for the final. 

Files related to the final:
Engine:
	BitArray .h/.cpp
	FixedSizeAllocator .h/.cpp
	MyMalloc .h/.cpp
	CombinedAllocators .h/.cpp	
	
FinalExamSampleProject:
	MemorySystem .h/.cpp
	Allocators .h/.cpp
	main.cpp

----------------------------------------------------------------------------------------------------------------------------------------------
	
Class Explanations:

BitArray
	Each FixedSizeAllocator holds one. Standard requirements of the BitArray Class.

FixedSizeAllocator
	Standard requirements of the FixedSizeAllocator Class. Several of these are managed by the combined allocator class instance.
	
MyMalloc
	Previous assignment's HeapManager. 

CombinedAllocators
	Singleton class that manages all allocation for the program. 
	Takes allocation requests from Allocators.cpp and passes them to various sized FixedSizeAllocators based on size defaulting to the heapmanager when necessary. 

MemorySystem
	When called from main the memory system initializes and destroys the CombinedAllocators Singleton Instance

Allocators 
	When called passes on allocation and free requests to the CombinedAllocators instance

----------------------------------------------------------------------------------------------------------------------------------------------

Unique Work
I'm not sure exactly what counts as unique so I'll just mention a few things. 

Design Patterns:
	CombinedAllocators implements the Singleton Pattern with only a single instance being allowed to handle memory management. 
	CombinedAllocators.h lines 17-20 have the private empty constructors and operators to enforce this. 
	CombinedAllocators.cpp lines 11-18 have the Instance Function that ensures the singleton. 
	
	BitArray implements the factory pattern. The skeleton in the slides having a static create function prompted this slight change. 
	BitArray.h lines 27,28 Are the deleted and private functions to hide creation logic from the outside. 
	BitArray.cpp lines 6-12 contains the static create function. lines 30-47 have an assignment operator. Copy Constructor is not allowed. 
	
GuardBanding
	I implemented variable patterned and sized guardbanding in the FixedSizeAllocator.
	It is currently using a single byte (0xCC) before and after the memory payload (FixedSizeAllocator.h line 20)
	When in a debug build the allocator checks the memory on free and reports and memory overwriting and the address it occurred. (FixedSizeAllocator.cpp lines 68-75)
