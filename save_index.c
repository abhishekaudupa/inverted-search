#include "save_index.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/*
   Function to save the inverted index database into a backup file.
 */
void save_database(const Word_List_Table *const index_table) {
    //design time check
    assert(index_table);

    //get the table.
    const Word_List_Header *table = index_table->table;

    //open the backup file.
    FILE *backup_file_ptr = fopen("backup.txt", "wb");

    //check file creation.
    if(!backup_file_ptr) {
	fprintf(stderr, "File creation failed.\n");
	return;
    }

    //iterate through the table.
    for(int i = 0; i < HASH_TABLE_SIZE; ++i) {

	//check if there is atleast one word list in the index.
	if(table[i].word_list_head) {

	    //get a traverser for word list.
	    Word_List_Node *word_trav = table[i].word_list_head;

	    //traverse the word list.
	    while(word_trav) {
		//print start magic character.
		fprintf(backup_file_ptr, "#");

		//print the word into the backup file.
		fprintf(backup_file_ptr, "%02d:%02hhd:%s:", i, (char)strlen(word_trav->word), word_trav->word);

		//alternative dump.
		//fprintf(backup_file_ptr, "%02d:%s:", i, word_trav->word);

		//get a traverser for file list.
		Word_File_List_Node *file_trav = word_trav->file_list_header.word_file_list_head;

		//traverse the file list.
		while(1) {

		    //print the filename into the backup file.
		    fprintf(backup_file_ptr, "%02hhd:%s:%d", (char)strlen(file_trav->filename), file_trav->filename, file_trav->word_repetetion_count);

		    //alternative dump.
		    //fprintf(backup_file_ptr, "%s:%d", file_trav->filename, file_trav->word_repetetion_count);

		    //goto next file.
		    file_trav = file_trav->next;

		    //append separator.
		    if(file_trav)
			fprintf(backup_file_ptr, ":");
		    else
			break;
		}

		//print end magic character.
		fprintf(backup_file_ptr, "#\n");

		//goto next word.
		word_trav = word_trav->next;
	    }
	}
    }

    //close file.
    fclose(backup_file_ptr);
}
