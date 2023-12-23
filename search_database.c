#include "search_database.h"
#include "display_index.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

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
