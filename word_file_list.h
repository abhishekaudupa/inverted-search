#ifndef WORD_FILE_LIST_H
#define WORD_FILE_LIST_H

#define FILENAME_LENGTH_MAX 50

typedef struct _Word_File_List {
    char filename[FILENAME_LENGTH_MAX];
    unsigned int word_count;
    struct _Word_File_List *next;
} Word_File_List;

#endif
