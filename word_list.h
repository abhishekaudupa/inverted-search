#ifndef WORD_LIST_H
#define WORD_LIST_H

#define WORD_LENGTH_MAX 20

#include "word_file_list.h"

//struct for a single word in the linked list of words in a hashtable index.
typedef struct _Word_List_Node {
    char word[WORD_LENGTH_MAX + 1];
    Word_File_List_Header file_list_header;
    struct _Word_List_Node *next;
} Word_List_Node;

//struct for linked list header.
typedef struct _Word_List_Header {
    Word_List_Node *word_list_head;
    unsigned int word_count;
} Word_List_Header;

//struct that will be saved in the backup file.
typedef struct _Word_Save_Format {
    char word[WORD_LENGTH_MAX + 1];
    unsigned int file_count;
} Word_Save_Format;

void insert_in_word_list(const char *const filename, const char *const word_buffer, Word_List_Header *const header);

Word_List_Node *allocate_word_list_node(const char *const word_buffer, const char *const filename);

Word_List_Header create_word_list_header();

#endif
