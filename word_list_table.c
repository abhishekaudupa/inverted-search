#include "word_list_table.h"
#include <assert.h>
#include <stdio.h>
#include "allocator.h"

/*
   Function to index contents of a word buffer into the index hash table.
 */
void index_word(const char *const filename, const char *const word_buffer, Word_List_Table *const index_table) {

    //design time check.
    assert(word_buffer);
    assert(index_table);

    //obtain the insertion index for the word.
    char insertion_index = get_word_insertion_index(word_buffer[0]);

    //insert the word at the calculated index.
    insert_at_index(filename, insertion_index, word_buffer, index_table);
}

/*
   Function to get the index into which a word is to be
   inserted in the hash table.
 */
char get_word_insertion_index(const char c) {
    
    //if c is a upper case letter.
    if(c >= 'A' && c <= 'Z')
	return c - 'A';

    //if c is a lower case letter.
    if(c >= 'a' && c <= 'z')
	return c - 'a';

    //otherwise return default index.
    return HASH_TABLE_SIZE - 1;
}

/*
   Function to insert the word in the hash table, at the given index.
 */
void insert_at_index(const char *const filename, const char insertion_index, const char *const word_buffer, Word_List_Table *const index_table) {
    //design time check.
    assert(insertion_index >= 0 && insertion_index < HASH_TABLE_SIZE);
    assert(word_buffer);
    assert(index_table);

    //insert the word into the word list.
    insert_in_word_list(filename, word_buffer, index_table->table + insertion_index);
}

/*
   Function to create an empty index table
 */
Word_List_Table *create_table() {
    
    //get a new table.
    Word_List_Table *index_table = get_memory(sizeof(*index_table));

    //set table contents to NULL.
    for(int i = 0; i < HASH_TABLE_SIZE; ++i) {
	((index_table->table)[i]).word_list_head = NULL;
	((index_table->table)[i]).word_count = 0;
    }

    return index_table;
}

void print_table(Word_List_Table *const index_table) {

    //design time check.
    assert(index_table);

    //traverse each index.
    for(int i = 0; i < HASH_TABLE_SIZE; ++i) {
	//get head of the word list in that index.
	Word_List_Header *header = index_table->table + i;

	printf("Index %d\n", i);
	//print the word list.
	print_word_list(header);
    }
}
