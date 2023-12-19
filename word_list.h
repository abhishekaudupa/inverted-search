#ifndef WORD_LIST_H
#define WORD_LIST_H

#define WORD_LENGTH_MAX 50

#include "word_file_list.h"

typedef struct _Word_List {
    char word[WORD_LENGTH_MAX];
    Word_File_List *head;
    struct _Word_List *next;
} Word_List;

#endif
