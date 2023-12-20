#include "word_list.h"
#include <assert.h>
#include <stdio.h>
#include "allocator.h"
#include <string.h>

void insert_in_word_list(const char *const filename, const char *const word_buffer, Word_List **head) {
    //design-time check.
    assert(filename);
    assert(word_buffer);
    assert(head);

    //check if the list is empty.
    if(!*head) {
	//allocate a Word_List node.
	Word_List *new_word = allocate_word_list_node(word_buffer, filename);

	if(!new_word) {
	    fprintf(stderr, "Memory allocation failed for inserting %s.\n", word_buffer);
	    return;
	}

	//set head to it.
	*head = new_word;

	return;
    }

    //traverse list if list isn't empty. Go below.

    //get a traverser and follower.
    Word_List *trav = *head;
    Word_List *foll = NULL;

    //traverse
    while(trav) {
	//compare with current word.
	int cmp = strcmp(word_buffer, trav->word);

	//there's a match.
	if(cmp == 0) {
	    //update count against the file.
	    insert_in_word_file_list(filename, &(trav->file_list_head));
	    return;
	} else if(cmp < 0) {
	    //insert word before current node.
	    
	    //allocate a Word_List node.
	    Word_List *new_word = allocate_word_list_node(word_buffer, filename);

	    //trav is non-head node.
	    if(foll) {
		//put new node after follower.
		foll->next = new_word;
		new_word->next = trav;

		return;
	    } else {	//trav is head node.
		//make new node the head.
		new_word->next = *head;
		*head = new_word;

		return;
	    }
	}

	//move forward.
	foll = trav;
	trav = trav->next;
    }

    //we'll have to inser the word in the end of list.
    
    //allocate a Word_List node.
    Word_List *new_word = allocate_word_list_node(word_buffer, filename);

    //make it the foll's next node.
    foll->next = new_word;

}

/*
   Function to get a dynamically allocated Word_List node.
 */
Word_List *allocate_word_list_node(const char *const word_buffer, const char *const filename) {
    //design time check.
    assert(word_buffer);

    //allocate a Word_List node.
    Word_List *new_word = get_memory(sizeof(*new_word));

    //check allocation.
    if(!new_word)
	return NULL;

    //populate it.
    strcpy(new_word->word, word_buffer);
    new_word->file_list_head = NULL;

    //insert the filename.
    insert_in_word_file_list(filename, &(new_word->file_list_head));

    //set its next pointer.
    new_word->next = NULL;

    return new_word;
}

void print_word_list(Word_List *const head) {

    //exit if list is empty.
    if(!head) {
	fprintf(stderr, "    Word List Empty.\n");
	return;
    }

    //proceed otherwise.

    //get a traverser.
    Word_List *trav = head;

    //traverse.
    while(trav) {
	//print the word.
	printf("    [%s]\n", trav->word);

	//print the files in which it appears.
	print_word_file_list(trav->file_list_head);

	//move on.
	trav = trav->next;
    }
}
