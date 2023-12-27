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
		
		//Word_Save_Format struct that goes into backup file.
		Word_Save_Format word_save_format;

		//save word metadata in the word save struct.
		strcpy(word_save_format.word, word_trav->word);
		word_save_format.file_count = word_trav->file_list_header.file_count;

		//write the struct to backup file.
		fwrite(&word_save_format, sizeof(word_save_format), 1, backup_file_ptr);

		//file write error check.
		if(feof(backup_file_ptr)) {
		    fprintf(stderr, "File write failed.\n");
		    return;
		}

		//get a traverser for file list.
		Word_File_List_Node *file_trav = word_trav->file_list_header.word_file_list_head;

		//traverse the file list.
		while(file_trav) {

		    //Word_File_Save_Format struct that goes into backup file.
		    Word_File_Save_Format word_file_save_format;

		    //save file metadata to file save struct.
		    strcpy(word_file_save_format.filename, file_trav->filename);
		    word_file_save_format.word_repetetion_count = file_trav->word_repetetion_count;

		    //write the struct to backup file.
		    fwrite(&word_file_save_format, sizeof(word_file_save_format), 1, backup_file_ptr);

		    //file write error check.
		    if(feof(backup_file_ptr)) {
			fprintf(stderr, "File write failed.\n");
			return;
		    }

		    //goto next file.
		    file_trav = file_trav->next;
		}

		//write a spacer char. at the end of each word file list.
		char c = 1;
		fwrite(&c, sizeof(c), 1, backup_file_ptr);

		//file write error check.
		if(feof(backup_file_ptr)) {
		    fprintf(stderr, "File write failed.\n");
		    return;
		}

		//goto next word.
		word_trav = word_trav->next;
	    }
	}
    }

    //overwrite end spacer character (0 to signify end).
    char c = 0;

    //seek to previous space character write position in file.
    fseek(backup_file_ptr, ftell(backup_file_ptr) - 1, SEEK_SET);
    
    //overwrite a zero.
    fwrite(&c, sizeof(c), 1, backup_file_ptr);

    //file write error check.
    if(feof(backup_file_ptr)) {
	fprintf(stderr, "File write failed.\n");
	return;
    }

    //close file.
    fclose(backup_file_ptr);
}
