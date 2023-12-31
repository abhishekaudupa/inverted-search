#include "search_index.h"
#include "display_index.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/*
   Function to search a given word in the index hash table.
   If the word index is not empty, it calls other functions to 
   search the word in word list.
 */
void search_database(const char *const word, const Word_List_Table *const index_table) {
    //design time check.
    assert(word);
    assert(index_table);

    //get the search index.
    int search_index = get_word_insertion_index(word[0]);

    //search for the word in the search index if there's a word list in that index.
    if((index_table->table)[search_index].word_list_head) {
	//search for the word in the word list.
	search_in_word_list(word, index_table->table + search_index);
    } else {
	fprintf(stderr, "%s is not in the database.\n", word);
    }
}

/*
   Function to search for the file in the word linked list.
   Once the word is found, it calls another function to print the file in which
   it appears along with the repetetion count.
 */
void search_in_word_list(const char *const word, const Word_List_Header *const header) {
    //design time check.
    assert(word);
    assert(header);

    //get a word list traverser.
    Word_List_Node *trav = header->word_list_head;

    //traverse the list.
    while(trav) {
	//compare the search word with the trav's word.
	if(strcmp(word, trav->word) == 0) {
	    //display message.
	    fprintf(stdout, "\"%s\" is found in the following files:\n", word);

	    //print file list.
	    print_word_file_list(&(trav->file_list_header));

	    //stop
	    return;
	}
	
	//move forward.
	trav = trav->next;
    }

    //word wasn't found in the list.
    fprintf(stdout, "%s is not in the database.\n", word);
}
