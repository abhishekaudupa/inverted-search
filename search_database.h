#ifndef SEARCH_DATABASE_H
#define SEARCH_DATABASE_H

#include "word_list_table.h"

void search_database(const char *const word, const Word_List_Table *const index_table);

void search_in_word_list(const char *const word, const Word_List_Header *const header);

#endif
