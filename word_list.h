#ifndef WORD_LIST_H
#define WORD_LIST_H

#define WORD_LENGTH_MAX 50

#include "word_file_list.h"

typedef struct _Word_List_Node {
    char word[WORD_LENGTH_MAX];
    Word_File_List_Header file_list_header;
    struct _Word_List_Node *next;
} Word_List_Node;

typedef struct _Word_List_Header {
    Word_List_Node *word_list_head;
    unsigned int word_count;
} Word_List_Header;

void insert_in_word_list(const char *const filename, const char *const word_buffer, Word_List_Header *const header);

Word_List_Node *allocate_word_list_node(const char *const word_buffer, const char *const filename);

void print_word_list(const Word_List_Header *const header);

Word_List_Header create_word_list_header();

#endif
