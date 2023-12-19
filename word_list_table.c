#include "word_list_table.h"
#include <assert.h>
#include <stdio.h>

/*
   Function to index contents of a word buffer into the index hash table.
 */
void index_word(const char *const filename, const char *const word_buffer, Word_List_Table *const index_table) {

    //design time check.
    assert(word_buffer);
    assert(index_table);

    char insertion_index = get_word_insertion_index(word_buffer[0]);
    printf("(%hhd) ", insertion_index);
    printf("%s", word_buffer);
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

