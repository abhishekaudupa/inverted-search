#include <stdio.h>
#include "create_index.h"
#include <assert.h>

/*
   Driver function to created inverted index database.
   Calls other helper functions to read words in a file and index 'em.
 */
Word_List_Table *create_database(const int argc, char **argv, char *arg_val_array) {
    //design time checks.
    assert(argc);
    assert(argv);
    assert(*argv);
    assert(arg_val_array);
    assert(arg_val_array[0] == 0);

    //hash table to index words from files.
    Word_List_Table *index_table = create_table();

    //iterate through each input filename.
    for(int i = 0; i < argc; ++i) {
	
	//proceed only if the file associated with it is valid.
	if(arg_val_array[i]) {

	    //open file.
	    FILE *fptr = fopen(argv[i], "rb");

	    //if file open fails, skip it.
	    if(!fptr) {
		fprintf(stderr, "Failed to open the file %s\n", argv[i]);
		continue;
	    }

	    //read file and create internal index (hashtable).
	    index_file_contents(argv[i], fptr, index_table);

	    //close file handle.
	    fclose(fptr);
	}
    }

    return index_table;
}

/*
   Function to index the file contents. Reads words in a file and 
   calls another helper function to index the word.
 */
void index_file_contents(const char *const filename, FILE *const fptr, Word_List_Table *const index_table) {
    //design time check.
    assert(fptr);

    //start reading words from file
    while(1) {
	//get a buffer to store each word.
	char word[WORD_LENGTH_MAX];

	//read an alphanumeric word from file into the buffer.
	fscanf(fptr, "%50[a-zA-Z0-9']", word);

	//if there was a read error, exit function.
	if(ferror(fptr)) {
	    fprintf(stderr, "Error while reading file %s.\n", filename);
	    return;
	}

	//if we just read EOF, exit loop.
	if(feof(fptr))
	    break;

	//index words with more than 1 letter.
	if(word[1])
	    index_word(filename, word, index_table);

	//discard special characters.
	fscanf(fptr, "%[^a-zA-Z0-9]", word);
    }
}
