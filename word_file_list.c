#include "word_file_list.h"
#include <assert.h>
#include "allocator.h"
#include <string.h>
#include <stdio.h>

/*
   Function to insert a file's name in the file list against a given word.
   This either adds a new file node or updates the word count in a node if
   the filename matches it.
 */
void insert_in_word_file_list(const char *const filename, Word_File_List **head) {
    //design time check.
    assert(filename);
    assert(head);

    //if list is empty.
    if(!*head) {
	//get a new file node.
	Word_File_List *new_file_entry = allocate_word_file_list_node(filename);

	//check allocation
	if(!new_file_entry) {
	    fprintf(stderr, "Memory alloation for filename failed.\n");
	    return;
	}

	//set head to the new node.
	*head = new_file_entry;

	return;
    }

    //if list isn't empty, search. Go below.

    //get a traverser and follower.
    Word_File_List *trav = *head;
    Word_File_List *foll = NULL;

    //traverse
    while(trav) {
	//compare input filename node filename.
	int cmp = strcmp(filename, trav->filename);

	//if match
	if(cmp == 0) {
	    //increase word count.
	    ++(trav->word_count);

	    return;
	}

	//not match. Insert filename before.
	if(cmp < 0) {
	    //get a new Word_File_List node.
	    Word_File_List *new_file_entry = allocate_word_file_list_node(filename);

	    //check allocation.
	    if(!new_file_entry) {
		fprintf(stderr, "Memory alloation for filename failed.\n");
		return;
	    }

	    //trav isn't head node.
	    if(foll) {
		//insert new file before trav.
		foll->next = new_file_entry;
		new_file_entry->next = trav;

		return;
	    } else {	//trav is head node.
		//insert new file before head.
		new_file_entry->next = *head;

		//make new file the new head.
		*head = new_file_entry;

		return;
	    }
	}

	//move forward.
	foll = trav;
	trav = trav->next;
    }

    //we're here: insert file at the end of list.
    
    //get a new Word_File_List node.
    Word_File_List *new_file_entry = allocate_word_file_list_node(filename);

    //make it the last node.
    foll->next = new_file_entry;

}

/*
   Function to get a dynamically allocated Word_List node.
 */
Word_File_List *allocate_word_file_list_node(const char *const filename) {
    //design time check.
    assert(filename);

    //allocate a Word_File_List node.
    Word_File_List *new_word_file = get_memory(sizeof(*new_word_file));

    //check allocation.
    if(!new_word_file)
	return NULL;

    //populate it.
    strcpy(new_word_file->filename, filename);
    new_word_file->word_count = 1;

    //set its next pointer.
    new_word_file->next = NULL;

    return new_word_file;
}

/*
   Function to print list of files along with the word count.
 */
void print_word_file_list(Word_File_List *const head) {

    //design time check.
    assert(head);

    //get a traverser.
    Word_File_List *trav = head;

    //traverse
    while(trav) {
	//print details.
	printf("       %s -> %d\n", trav->filename, trav->word_count);

	//move on.
	trav = trav->next;
    }
}
