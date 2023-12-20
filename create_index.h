#ifndef CREATE_INDEX_H
#define CREATE_INDEX_H

#include "word_list_table.h"

Word_List_Table *create_database(const int argc, char **argv, char *arg_val_array);

void index_file_contents(const char *const filename, FILE *const fptr, Word_List_Table *const index_table);

#endif
