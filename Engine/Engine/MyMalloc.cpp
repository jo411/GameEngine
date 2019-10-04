#include "MyMalloc.h"
#include <cstdio>

MyMalloc::MyMalloc()
{
}


MyMalloc::~MyMalloc()
{
}

void MyMalloc::init(void * memory, size_t sizeMemory)
{		
	free_list_start = nullptr;
	first_page = nullptr;
	extend(sizeMemory, memory);
}


void * MyMalloc::extend(size_t asize, void* memory)
{	
		char* pp;//page pointer
		char* bp;//new block pointer
		
		pp =(char*) memory;//process input memory


	  //give new page sentinals
		
	
		PUT(pp + sizeof(page_header), PACK(2 * WORD_SIZE, 1));//prologue header

		PUT(pp + sizeof(page_header) + WORD_SIZE, PACK(2 * WORD_SIZE, 1));//prologue footer

		PUT(pp + asize - WORD_SIZE, PACK(0, 1));//epilogue header


	  //create a free block for the remaining space
		size_t blockSize = asize - sizeof(page_header) - 3 * WORD_SIZE;
		bp = FIRST_BLKP(pp);//get the location of the first block pointer
		PUT(HDRP(bp), PACK(blockSize, 0));
		PUT(FTRP(bp), PACK(blockSize, 0));


		//Add new page to the start of the list of pages
		page_header* ph = (page_header*)(pp);

		if (first_page == nullptr)//first allocation set the list starters
		{
			first_page = (page_header*)pp;
			first_page->next = nullptr;
			first_page->prev = nullptr;
			first_page->size = asize;
		}
		else//update linked list
		{
			ph->next = first_page;
			ph->prev = nullptr;
			ph->size = asize;
			first_page->prev = ph;
			first_page = ph;


		}


		if (free_list_start == nullptr)//if there isn't a list start
		{
			//create first entry in free list
			free_list_start = (free_header*)bp;
			free_list_start->next = nullptr;
			free_list_start->prev = nullptr;
		}
		else
		{
			insert_into_free(bp); //move the first pointer to ph
		}
	
		return nullptr;//bp;//return the new payload poitner

	
}

//update connections and make the new free element the start of the list

void MyMalloc::insert_into_free(void * bp)
{
	free_header* fh = (free_header*)bp;
	fh->next = free_list_start;
	free_list_start->prev = fh;
	fh->prev = nullptr;
	free_list_start = fh;
}

/*
 * Searches through the free list for blocks that can hold the requested (aligned) size
 */
void * MyMalloc::findFit(size_t size)
{
	free_header* fh;
	fh = free_list_start;
	if (fh == NULL) { return NULL; }
	while ((fh->next) && (GET_SIZE(HDRP(fh)) < size))//loop while the current node has a next until a block of sufficient size is found
	{
		fh = fh->next;
	}

	if (GET_SIZE(HDRP(fh)) >= size)//if the block that ended the loop was of valid size
	{
		return fh;
	}
	else//hit the end of the list without finding anything
	{

		return NULL;
	}
}

/*
 * Mark a block as allocated and split if needed
 */
void MyMalloc::set_allocated(void * bp, size_t size)
{
	size_t blockSize = GET_SIZE(HDRP(bp));


	size_t extra_size = GET_SIZE(HDRP(bp)) - size;//get overflow */

	if (extra_size > ALIGN(MIN_BLOCK_SIZE))//if the leftover can hold a free list payload( by extension header+footer+16 bytes) then split it
	{


		//assign current block
		PUT(HDRP(bp), PACK(size, 1));
		PUT(FTRP(bp), PACK(size, 1));
		
		void* bpNext = NEXT_BLKP(bp);//get next block
		PUT(HDRP(bpNext), PACK(extra_size, 0));//mark the leftover space as unallocated
		PUT(FTRP(bpNext), PACK(extra_size, 0));
		//Not using coalesce yet
		insert_into_free(bpNext);
		remove_from_free(bp);//remove from free NOTE may proc a memory request, amortizing here could save time later
		//coalesce(bp);//add the new block to the free list




	}
	else//assign the whole block
	{
		PUT(HDRP(bp), PACK(blockSize, 1));
		PUT(FTRP(bp), PACK(blockSize, 1));//LINE WHERE IT ALL BREAKS!!!
		remove_from_free(bp);
	}



}

/*
 * remove a block from the free list
 */
void MyMalloc::remove_from_free(void * bp)
{
	free_header* fh = (free_header*)bp;

	if (fh->prev)//if a previous exists
	{
		if (fh->next)//middle node
		{
			fh->prev->next = fh->next;//make the previous skip current
			fh->next->prev = fh->prev;

		}
		else//tail node
		{
			fh->prev->next = NULL;
		}
	}
	else//no prev means this is the first item
	{
		if (!fh->next)//if there is no next this is the only item in the list
		{
			free_list_start = NULL;//no more free space
			//extend(1);// request a minimum sized page
			return;
		}

		free_list_start = fh->next;
		free_list_start->prev = NULL;//erase pointer back to fh
	}

	return;

}



/*
 *Takes the requested size and finds a block for it
 */
void * MyMalloc::mm_malloc(size_t size)
{
	if (size == 0) { return NULL; }//don't use zero size

	int newSize = ALIGN(MAX(MIN_BLOCK_SIZE, size + OVERHEAD));//always have room in the payload for a free list header and ensure if the size requested is bigger that the header overhead is added on


	void* bp = findFit(newSize);
	if (bp == NULL)//no block found
	{
		//bp = extend(newSize);//request more memory
		return nullptr;//in this case return null: no memory left
	}

	//found  a block, allocate it
	set_allocated(bp, newSize);


	return bp;

}
void MyMalloc::printFreeList()
{
	printf("\n\nFree List: ");
	free_header* current = free_list_start;
	while (current != NULL)
	{
		printf("Free Block at: %p\n", current);

		if (current->prev == NULL)
		{
			printf("No previous\n");
		}
		else
		{
			printf("prev at: %p\n", current->prev);
		}

		if (current->next == NULL)
		{
			printf("No next\n");
		}
		else
		{
			printf("next at: %p\n", current->next);
		}

		printf("Size: %zu\n", GET_SIZE(HDRP(current)));
		printf("\n");
		current = current->next;
	}
}

void MyMalloc::printMemory()
{
	page_header* current = first_page;
	while (current != NULL)
	{
		printf("Page header at: %p\n", current);

		if (current->prev == NULL)
		{
			printf("No previous\n");
		}
		else
		{
			printf("prev at: %p\n", current->prev);
		}

		if (current->next == NULL)
		{
			printf("No next\n");
		}
		else
		{
			printf("next at: %p\n", current->next);
		}

		printf("Size of: %zu\n", current->size);

		printPage((char*)current);

		current = current->next;
	}
}

void MyMalloc::printPage(char* ph)
{
	printf("\nPage Details: \n");
	char* bp = FIRST_BLKP(ph);
	printf("Block at: %p\n", bp);
	printf("Size of: %zu\n", GET_SIZE(HDRP(bp)));
	printf("Allocated: %s\n", (GET_ALLOC(HDRP(bp)) == 0) ? "NO" : "YES");
	printf("\n");

	bp = NEXT_BLKP(bp);

	while (GET_SIZE(HDRP(bp)) > 0)
	{
		printf("Block at: %p\n", bp);
		printf("Size of: %zu\n", GET_SIZE(HDRP(bp)));
		printf("Allocated: %s\n", (GET_ALLOC(HDRP(bp)) == 0) ? "NO" : "YES");
		printf("\n");

		bp = NEXT_BLKP(bp);
	}


}

