#ifndef WORD_LIST_H
#define WORD_LIST_H

#define WORD_LENGTH_MAX 50

#include "word_file_list.h"

typedef struct _Word_List {
    char word[WORD_LENGTH_MAX];
    Word_File_List *file_list_head;
    struct _Word_List *next;
} Word_List;

void insert_in_word_list(const char *const filename, const char *const word_buffer, Word_List **head);

Word_List *allocate_word_list_node(const char *const word_buffer, const char *const filename);

void print_word_list(Word_List *const head);

#endif
