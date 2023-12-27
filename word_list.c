#include "word_list.h"
#include <assert.h>
#include <stdio.h>
#include "allocator.h"
#include <string.h>

/*
   Function to insert the given word in the word linked list.
   This inserts a new word node if the word doesn't exist.
   It calls other function to update the filelist for the file
   in which the word appears.
 */
void insert_in_word_list(const char *const filename, const char *const word_buffer, Word_List_Header *const header) {
    //design-time check.
    assert(filename);
    assert(word_buffer);
    assert(header);

    //check if the list is empty.
    if(!(header->word_list_head)) {
	//allocate a Word_List_Node node.
	Word_List_Node *new_word = allocate_word_list_node(word_buffer, filename);

	if(!new_word) {
	    fprintf(stderr, "Memory allocation failed for inserting %s.\n", word_buffer);
	    return;
	}

	//set head to it.
	header->word_list_head = new_word;

	//set word count.
	header->word_count = 1;

	return;
    }

    //traverse list if list isn't empty. Go below.

    //get a traverser and follower.
    Word_List_Node *trav = header->word_list_head;
    Word_List_Node *foll = NULL;

    //traverse
    while(trav) {
	//compare with current word.
	int cmp = strcmp(word_buffer, trav->word);

	//there's a match.
	if(cmp == 0) {
	    //update count against the file.
	    insert_in_word_file_list(filename, &(trav->file_list_header));
	    return;
	}

	if(cmp < 0) {
	    //insert word before current node.

	    //allocate a Word_List_Node node.
	    Word_List_Node *new_word = allocate_word_list_node(word_buffer, filename);

	    //check allocation.
	    if(!new_word) {
		fprintf(stderr, "Memory alloation for word insertion failed.\n");
		return;
	    }

	    //increment word count.
	    ++(header->word_count);

	    //trav is non-head node.
	    if(foll) {
		//put new node after follower.
		foll->next = new_word;
		new_word->next = trav;

		return;
	    } else {	//trav is head node.
			//make new node the head.
		new_word->next = header->word_list_head;
		header->word_list_head = new_word;

		return;
	    }

	}

	//move forward.
	foll = trav;
	trav = trav->next;
    }

    //we'll have to inser the word in the end of list.

    //allocate a Word_List_Node node.
    Word_List_Node *new_word = allocate_word_list_node(word_buffer, filename);
    
    //check allocation.
    if(!new_word)
	return;

    //increment word count.
    ++(header->word_count);

    //make it the foll's next node.
    foll->next = new_word;
}

/*
   Function to get a dynamically allocated Word_List_Node node.
 */
Word_List_Node *allocate_word_list_node(const char *const word_buffer, const char *const filename) {
    //design time check.
    assert(word_buffer);

    //allocate a Word_List_Node node.
    Word_List_Node *new_word = get_memory(sizeof(*new_word));

    //check allocation.
    if(!new_word)
	return NULL;

    //populate it.
    strcpy(new_word->word, word_buffer);
    new_word->file_list_header = create_word_file_list_header();

    //insert the filename.
    insert_in_word_file_list(filename, &(new_word->file_list_header));

    //set its next pointer.
    new_word->next = NULL;

    return new_word;
}

/*
   Function to create a word list header.
 */
Word_List_Header create_word_list_header() {
    //crete the return variable.
    Word_List_Header word_list_header;

    //init the header.
    word_list_header.word_list_head = NULL;
    word_list_header.word_count = 0;

    return word_list_header;
}
