#pragma once
class MyMalloc
{
private:

	/*Program Macros*/

/* always use 16-byte alignment */
#define ALIGNMENT 16

/*Size of a size_t*/
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

/*Size of headers and footer "words" stored as size_t's*/
#define WORD_SIZE (sizeof(size_t))

/*set a chunk to be 4 words*/
#define CHUNK_SIZE (1<<14)

/*Gets the extra size required to hold a payload*/
#define OVERHEAD (sizeof(block_header)+sizeof(block_footer))

/*Defines the smallest size that a block can be to make sure that a free header can always be placed in the payload*/
#define MIN_BLOCK_SIZE (OVERHEAD+sizeof(free_header))

	/*Part of accessing a word*/
#define GET(p) (*reinterpret_cast<size_t*>(p))

	/*Tools for accessing header/footer fields*/
#define GET_SIZE(p) (GET(p) & ~0xF)//This assumes 16bit allignment can change for any other size
#define GET_ALLOC(p) (GET(p) & 0x1)
#define PUT(p,val)(*reinterpret_cast<size_t*>(p)=(val))//install data
#define PACK(size,alloc)((size) | (alloc))//pack bits



	/*Program Inline Functions*/


/* rounds up to the nearest multiple of ALIGNMENT */
//#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
	inline size_t ALIGN(size_t size)const { return (((size)+(ALIGNMENT - 1)) & ~(ALIGNMENT - 1)); }

/*Size of the overhead required to track a page*/
//#define PAGE_OVERHEAD ((sizeof(page_header)+3*WORD_SIZE+sizeof(block_header)))
	inline size_t PAGE_OVERHEAD()const { return ((sizeof(page_header) + 3 * WORD_SIZE + sizeof(block_header))); }


/*Align a chunk*/
//#define CHUNK_ALIGN(size) (((size)+(CHUNK_SIZE-1))&~(CHUNK_SIZE-1))
	inline size_t CHUNK_ALIGN(size_t size)const {return (((size)+(CHUNK_SIZE - 1))&~(CHUNK_SIZE - 1));}

/*Max value of 2 values*/
//#define MAX(x, y) ((x) > (y) ? (x) : (y))
	inline size_t MAX(size_t x, size_t y)const { return  ((x) > (y) ? (x) : (y)); }
	
/*find header by payload pointer*/
//#define HDRP(bp) (reinterpret_cast<char*>(bp)-sizeof(block_header))	
	inline char* HDRP(void* bp)const { return (reinterpret_cast<char*>(bp) - sizeof(block_header)); }

/*find a footer by block pointer*/
//#define FTRP(bp) (reinterpret_cast<char*>(bp)+GET_SIZE(HDRP(bp))-OVERHEAD)
	inline char* FTRP(void* bp)const { return (reinterpret_cast<char*>(bp) + GET_SIZE(HDRP(bp)) - OVERHEAD); }

/*Gets the block pointer of the first block in a page*/
//#define FIRST_BLKP(pp) (reinterpret_cast<char*>(pp)+sizeof(page_header)+2*WORD_SIZE+sizeof(block_header))//get the first block header of a given pagePointer factoring in a page header and the two sentinals
	inline char* FIRST_BLKP(char* pp)const { return (reinterpret_cast<char*>(pp) + sizeof(page_header) + 2 * WORD_SIZE + sizeof(block_header)); }

/*gets the next/previous header by a payload pointer*/
#define NEXT_BLKP(bp)(reinterpret_cast<char*>(bp)+GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp)(reinterpret_cast<char*>(bp)-GET_SIZE((char*)(bp)-OVERHEAD))


/*free list struct*/	

	struct free_header {
		free_header* next;
		free_header* prev;
	};


	/*Header and Footer words*/
	typedef size_t block_header;

	typedef size_t block_footer;

	/*page list structs*/	

	struct page_header {
		size_t size;
		page_header* next;
		page_header* prev;
	};



	/*List starts*/

	/*First page in the pages linked list*/
	page_header* first_page;

	/*First page in the free list*/
	free_header* free_list_start;//start of free list


public:
	MyMalloc();
	~MyMalloc();
	//Internal methods
	void init(void * memory, size_t sizeMemory);//take in memory and create data structures 
	void* mm_malloc(size_t size);//return a pointer to a block of memory of size bytes. Or nullptr if no memory
	bool mm_free(void* bp);//release a pointer to a block of memory managed by this manager
	size_t GetTotalFreeMemory()const;
	bool contains(const void* ptr)const;
	bool IsAllocated(void* ptr)const;
	size_t GetLargestFreeBlock()const;
	void printFreeList()const;//display all available blocks
	void printMemory()const;//display the status of the heap including free and outstanding allocations

private:
	size_t usedMemory;//how much memory is currently allocated
	size_t totalMemory;//total memory given to the manager
	void* extend(size_t asize, void* memory);//Currently only gets called once to set up with initial memory. Can be used to ask for more memory from the OS
	void insert_into_free(void* bp);//take a block pointer and insert it into the free list (Explicit free list)
	void* findFit(size_t size);//find and return a pointer to the next open block >= size bytes (First fit)
	void set_allocated(void* bp, size_t size); // mark a block descriptor and it's payload as allocated 
	void remove_from_free(void* bp);//remove a block descriptor from the freelist
	void coalesce(void* bp);//Collapse nearby free blocks into one large block
	void printPage(char * ph)const;//print the status of a specific page of memory
};

