#ifndef WORD_LIST_TABLE_H
#define WORD_LIST_TABLE_H

#include "word_list.h"

#define HASH_TABLE_SIZE 27

typedef struct _Word_List_Table {
    Word_List_Header table[HASH_TABLE_SIZE];
} Word_List_Table;

void index_word(const char *const filename, const char *const word_buffer, Word_List_Table *const index_table);

char get_word_insertion_index(const char c);

void insert_at_index(const char *const filename, const char insertion_index, const char *const word_buffer, Word_List_Table *const index_table);

Word_List_Table *create_table();

void print_table(Word_List_Table *const index_table);

#endif
