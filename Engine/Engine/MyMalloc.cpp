#include "MyMalloc.h"

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
	//extend(mem_pagesize()*init_page_mult);//request an initial block based on the init var	
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

void MyMalloc::insert_into_free(void * bp)
{
	free_header* fh = (free_header*)bp;
	fh->next = free_list_start;
	free_list_start->prev = fh;
	fh->prev = nullptr;
	free_list_start = fh;
}

