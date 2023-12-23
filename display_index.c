#include "display_index.h"
#include <assert.h>
#include <stdio.h>

/*
   Function to display the hash table contents i.e the inverted index.
 */
void display_database(const Word_List_Table *const index_table) {

    //if we haven't created index database yet.
    if(!index_table) {
	fprintf(stderr, "Database not created yet.\n");
	return;
    }

    //iterate through index table.
    for(int i = 0; i < HASH_TABLE_SIZE; ++i) {

	//get the word list header pointer in that index.
	const Word_List_Header *const header = index_table->table + i;

	//print the index.
	fprintf(stdout, "Index %d: %u words\n", i, header->word_count);

	//print the list of words.
	print_word_list(header);
    }
}

/*
   Function to print list of words indexed.
 */
void print_word_list(const Word_List_Header *const header) {

    //design time check.
    assert(header);

    //exit if list is empty.
    if(!(header->word_list_head)) {
	fprintf(stderr, "    No words.\n");
	return;
    }

    //proceed otherwise.

    //get a traverser.
    Word_List_Node *trav = header->word_list_head;

    //traverse.
    while(trav) {
	//print the word.
	fprintf(stdout, "    [%s]", trav->word);

	//get the file list header.
	Word_File_List_Header *header = &(trav->file_list_header);

	//print the file count.
	fprintf(stdout, ": %u files\n", header->file_count);

	//print the files in which it appears.
	print_word_file_list(header);

	//move on.
	trav = trav->next;
    }
}

/*
   Function to print list of files along with the word count.
 */
void print_word_file_list(Word_File_List_Header *const header) {

    //design time check.
    assert(header);

    //get a traverser.
    Word_File_List_Node *trav = header->word_file_list_head;

    //traverse
    while(trav) {
	//print details.
	fprintf(stdout, "       %s -> %d count\n", trav->filename, trav->word_repetetion_count);

	//move on.
	trav = trav->next;
    }
}

