#include "update_index.h"
#include <assert.h>
#include <string.h>
#include "display_index.h"
#include <stdlib.h>

/*
   Function to read from a file into buffer.
 */
int read_file(FILE *const fptr, char *const buffer, const int size) {
    //design time check.
    assert(fptr);
    assert(buffer);

    //read into file.
    fread(buffer, size, 1, fptr);

    //check for read error.
    if(ferror(fptr))
	return -1;

    //check for end of file.
    if(feof(fptr))
	return -2;

    //success
    return 1;
}

/*
   Function to read and verify the separator.
 */
int read_and_check_separator(FILE *const fptr) {
    //design time check.
    assert(fptr);

    //to store the separator character.
    char separator;

    //read the separator.
    int read_status = read_file(fptr, &separator, 1);
    if(read_status == -1 || read_status == -2) {
	fprintf(stderr, "Invalid backup file.\n");
	return read_status;
    }

    //check separator.
    if(separator != ':') {
	fprintf(stderr, "Invalid backup file.\n");
	return -3;
    }

    //success.
    return 1;
}

/*
   Function to read a filename or word in the backup file.
   Word is formatted as:
   [word_string length, 2 chars]:[word]:
 */
int read_name(FILE *const fptr, char *const buffer) {
    //read word length.
    char name_len[3] = { 0 };
    int read_stat = read_file(fptr, name_len, sizeof(name_len) - 1);
    if(read_stat == -1 || read_stat == -2) {
	fprintf(stderr, "Invalid backup file.\n");
	return read_stat;
    }

    //convert index to integral data and check.
    long name_len_int = strtol(name_len, NULL, 10);

    //check separator.
    read_stat = read_and_check_separator(fptr);
    if(read_stat == -1 || read_stat == -2 || read_stat == -3) {
	fprintf(stderr, "Invalid backup file.\n");
	return read_stat;
    }

    //to store the word.
    read_stat = read_file(fptr, buffer, name_len_int);
    if(read_stat == -1 || read_stat == -2 || read_stat == -3) {
	fprintf(stderr, "Invalid backup file.\n");
	return read_stat;
    }

    //append null character.
    buffer[name_len_int] = 0;

    //check separator.
    read_stat = read_and_check_separator(fptr);
    if(read_stat == -1 || read_stat == -2 || read_stat == -3) {
	fprintf(stderr, "Invalid backup file.\n");
	return read_stat;
    }

    //success.
    return 1;
}

/*
   Function to read word repetetion count.
   Format is number followed by a ':' or '#'.
 */
int read_word_count(FILE *const fptr, char *const buffer) {
    //design time check.
    assert(fptr);
    assert(buffer);

    //buffer index.
    int i = 0;

    while(i < 10) {
	//read digit.
	int read_stat = read_file(fptr, buffer + i, 1);
	if(read_stat == -1 || read_stat == -2) {
	    fprintf(stderr, "Invalid backup file.\n");
	    return read_stat;
	}

	//check for terminator.
	if(buffer[i] == ':') {
	    //end of file list.
	    return 1;
	}

	//check for terminator.
	if(buffer[i] == '#') {
	    //end of line.
	    return 2;
	}

	//check for digit.
	if(!(buffer[i] >= '0' && buffer[i] <= '9')) {
	    fprintf(stderr, "Invalid backup file.\n");
	    return -3;
	}

	//increment buffer index.
	++i;
    }

    //should have atmost 10 digits.
    return -3;
}

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

    while(1) {
	//read magic character
	char magic_char;
	int read_stat = read_file(backup_file, &magic_char, sizeof(magic_char));
	if(read_stat == -1 || read_stat == -2) {
	    fprintf(stderr, "RS:%d.Invalid backup file.\n", read_stat);
	    return;
	}

	//check magic character
	if(magic_char != '#') {
	    fprintf(stderr, "Invalid backup file2.\n");
	    return;
	}

	//read index number.
	char index[3] = { 0 };
	read_stat = read_file(backup_file, index, sizeof(index) - 1);
	if(read_stat == -1 || read_stat == -2) {
	    fprintf(stderr, "Invalid backup file3.\n");
	    return;
	}

	//check index digits.
	if(!((index[0] >= '0' && index[0] <= '9')
		&& (index[1] >= '0' && index[1] <= '9'))) {
	    fprintf(stderr, "Invalid backup file4.\n");
	    return;
	}

	//convert index to integral data and check.
	long index_int = strtol(index, NULL, 10);
	if(!(index_int >= 0 && index_int <= 26)) {
	    fprintf(stderr, "Invalid backup file5.\n");
	    return;
	}

	//check separator.
	read_stat = read_and_check_separator(backup_file);
	if(read_stat == -1 || read_stat == -2 || read_stat == -3) {
	    fprintf(stderr, "Invalid backup file6.\n");
	    return;
	}

	//read the word.
	char word[WORD_LENGTH_MAX];
	read_stat = read_name(backup_file, word);
	if(read_stat == -1 || read_stat == -2 || read_stat == -3) {
	    fprintf(stderr, "Invalid backup file7.\n");
	    return;
	}

	//read all files
	while(1) {
	    //read filename.
	    char filename[FILENAME_LENGTH_MAX];
	    read_stat = read_name(backup_file, filename);
	    if(read_stat == -1 || read_stat == -2 || read_stat == -3) {
		fprintf(stderr, "Invalid backup file8.\n");
		return;
	    }

	    //read word count.
	    char word_count[10] = { 0 };
	    read_stat = read_word_count(backup_file, word_count);
	    if(read_stat == -1 || read_stat == -2 || read_stat == -3) {
		fprintf(stderr, "Invalid backup file9.\n");
		return;
	    }

	    long word_count_int = strtol(word_count, NULL, 10);

	    //push the word along with filename into the index table.
	    for(int i = 0; i < word_count_int; ++i) {
		index_word(filename, word, index_table);
	    }

	    //we've encountered line ending #.
	    if(read_stat == 2)
		break;
	}

	//read a character after line ending #.
	char c;
	fread(&c, 1, 1, backup_file);

	//exit loop if end of file.
	if(feof(backup_file)) {
	    fprintf(stderr, "Invalid backup file10.\n");
	    return;
	}
	
	//check the character for newline.
	if(c != '\n') {
	    fprintf(stderr, "Invalid backup file11.\n");
	    return;
	}

	//read another character.
	fread(&c, 1, 1, backup_file);

	//check for EOF
	if(feof(backup_file)) {
	    break;
	}

	//backtrack if not the end.
	fseek(backup_file, ftell(backup_file) - 1, SEEK_SET);
    }

    //display the database after reading from file.
    display_database(index_table);
}
