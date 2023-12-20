#ifndef WORD_FILE_LIST_H
#define WORD_FILE_LIST_H

#define FILENAME_LENGTH_MAX 50

typedef struct _Word_File_List {
    char filename[FILENAME_LENGTH_MAX];
    unsigned int word_repetetion_count;
    struct _Word_File_List *next;
} Word_File_List;

void insert_in_word_file_list(const char *const filename, Word_File_List **head);

Word_File_List *allocate_word_file_list_node(const char *const filename);

void print_word_file_list(Word_File_List *const head);

#endif
