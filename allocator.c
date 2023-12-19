#include "allocator.h"
#include <assert.h>
#include <stdio.h>

//memory tracker list head.
static Alloc_Mem_List *head = NULL;

//lock for the allocate_memory() function.
static int lock = 1;

void *get_memory(const size_t n_bytes) {
    
    //to return allocated memory.
    void *mem_ptr = NULL;

    //unlock the allocate_memory function.
    lock = 0;

    //allocate memory dynamically.
    mem_ptr = allocate_memory(n_bytes);

    //lock the allocate_memory function.
    lock = 1;

    //track the allocation, if allocation succeeded.
    if(mem_ptr)
	track_mem(mem_ptr);

    return mem_ptr;
}

void *allocate_memory(const size_t n_bytes) {

    //design time ensuring no other outside function
    //calls this function.
    assert(lock != 1);
    
    //to return allocated memory.
    void *mem_ptr = NULL;

    //to keep track of allocation attempts.
    int alloc_attempt = MAX_MEM_ALLOC_ATTEMPTS;

    //make attempts to allocate memory.
    while(!mem_ptr && alloc_attempt) {
	mem_ptr = malloc(n_bytes);
	--alloc_attempt;
    }

    printf("Allocated memory: %p of size %zu\n", mem_ptr, n_bytes);
    return mem_ptr;
}

void free_memory(void *mem) {

    //null ptr input.
    if(!mem)
	return;

    //get traversers to traverse Alloc_Mem_List.
    Alloc_Mem_List *trav = head;
    Alloc_Mem_List *foll = NULL;

    //traverse through list.
    while(trav) {
	//check for mem. match
	if(trav->mem == mem) {
	    printf("Freeing %p\n", trav->mem);
	    //release memory.
	    free(trav->mem);

	    if(foll) {
	    //link follower to trav's next.
	    foll->next = trav->next;
	    } else {
		head = NULL;
	    }

	    printf("Freeing %p\n", trav->mem);
	    //free traverser.
	    free(trav);

	    return;
	}

	//traverse forward.
	foll = trav;
	trav = trav->next;
    }
}

Status track_mem(void *mem) {

    //design time check.
    assert(mem);

    //unlock the allocate_memory function.
    lock = 0;

    //allocate mem. for Alloc_Mem_List node.
    Alloc_Mem_List *new = allocate_memory(sizeof(*new));

    //lock the allocate_memory function.
    lock = 1;

    //handle allocation failure.
    if(!new)
	return s_failure;

    //store the memory that is to be tracked.
    new->mem = mem;

    //set new's next to head.
    new->next = head;

    //make the head point to new.
    head = new;

    return s_success;
}

void free_all_memory() {

    //get traversers to traverse Alloc_Mem_List.
    Alloc_Mem_List *trav = head;
    Alloc_Mem_List *foll = NULL;

    while(trav) {

	//increment follower.
	foll = trav;

	//increment traverser.
	trav = trav->next;

	printf("Freeing %p\n", foll->mem);
	//release memory inside the follower.
	free(foll->mem);

	printf("Freeing %p\n", foll);
	//release the follower itself.
	free(foll);
    }
}
