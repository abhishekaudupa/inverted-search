#ifndef DISPLAY_INDEX_H
#define DISPLAY_INDEX_H

#include "word_list_table.h"

void display_database(const Word_List_Table *const index_table);

void print_word_list(const Word_List_Header *const header);

void print_word_file_list(Word_File_List_Header *const header);

#endif
