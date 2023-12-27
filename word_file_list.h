#ifndef WORD_FILE_LIST_H
#define WORD_FILE_LIST_H

#define FILENAME_LENGTH_MAX 20

//struct for one filename in the word list (a linked list node).
typedef struct _Word_File_List_Node {
    char filename[FILENAME_LENGTH_MAX + 1];
    unsigned int word_repetetion_count;
    struct _Word_File_List_Node *next;
} Word_File_List_Node;

//struct to act as the header for linked list.
typedef struct _Word_File_List_Header {
    Word_File_List_Node *word_file_list_head;
    unsigned int file_count;
} Word_File_List_Header;

//struct that will be saved in the backup file.
typedef struct _Word_File_Save_Format {
    char filename[FILENAME_LENGTH_MAX + 1];
    unsigned int word_repetetion_count;
} Word_File_Save_Format;

void insert_in_word_file_list(const char *const filename, Word_File_List_Header *const header);

Word_File_List_Node *allocate_word_file_list_node(const char *const filename);

Word_File_List_Header create_word_file_list_header();

#endif
