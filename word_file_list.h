#ifndef WORD_FILE_LIST_H
#define WORD_FILE_LIST_H

#define FILENAME_LENGTH_MAX 50

typedef struct _Word_File_List_Node {
    char filename[FILENAME_LENGTH_MAX];
    unsigned int word_repetetion_count;
    struct _Word_File_List_Node *next;
} Word_File_List_Node;

typedef struct _Word_File_List_Header {
    Word_File_List_Node *word_file_list_head;
    unsigned int file_count;
} Word_File_List_Header;

void insert_in_word_file_list(const char *const filename, Word_File_List_Node **head);

Word_File_List_Node *allocate_word_file_list_node(const char *const filename);

void print_word_file_list(Word_File_List_Node *const head);

#endif
