#include "update_index.h"
#include <assert.h>
#include <string.h>
#include "display_index.h"

/*
   Function to read inverted index from a backup file and display it.
 */
void update_database(Word_List_Table *const index_table) {
    
    //open the file "backup.txt"
    FILE *backup_file = fopen("backup.txt", "rb");

    //no such file.
    if(!backup_file) {
	fprintf(stderr, "Opening backup.txt failed.\n");
	return;
    }

    //structs that are stored in a legal backup file for each word and filename.
    Word_Save_Format word_save_format;
    Word_File_Save_Format word_file_save_format;

    //read the file till the end.
    while(1) {
	
	//read a single word struct.
	fread(&word_save_format, sizeof(word_save_format), 1, backup_file);

	//check for end of file (implies invalid backup file).
	if(feof(backup_file)) {
	    fprintf(stderr, "Word error: Invalid backup file.\n");
	    return;
	}

	//file count of the current word.
	unsigned int file_count = word_save_format.file_count;

	//read the filenames in which the word is present.
	for(int i = 0; i < file_count; ++i) {
	    
	    //read the filename struct.
	    fread(&word_file_save_format, sizeof(word_file_save_format), 1, backup_file);

	    //check for end of file (implies invalid backup file).
	    if(feof(backup_file)) {
		fprintf(stderr, "Filename error: Invalid backup file.\n");
		return;
	    }

	    //index the word, along with filename, as many times as it is repeated.
	    for(int i = 0; i < word_file_save_format.word_repetetion_count; ++i)
		index_word(word_file_save_format.filename, word_save_format.word, index_table);
	}

	//read the spacing character.
	char c;
	fread(&c, sizeof(c), 1, backup_file);

	if(feof(backup_file)) {
	    fprintf(stderr, "Spacing char. error: Invalid backup file.\n");
	    return;
	}

	//check the spacing character.
	if(c == 0)
	    break;
    }

    //display the database after reading from file.
    display_database(index_table);
}
