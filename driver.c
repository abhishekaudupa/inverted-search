#include <stdio.h>
#include "argument.h"
#include "create_index.h"
#include "word_list_table.h"
#include "allocator.h"
#include "display_index.h"
#include "search_index.h"
#include "save_index.h"
#include "update_index.h"

/*
   DOCUMENTATION

   SUMMARY:
   This inverted index creation program reads each word in the input files, 
   puts the words in a hash table along with the list of files in which they 
   appear and the number of times they appear.

   CREATING INDEX:
   The hash table is an array of 27 cells, each of which store the linked 
   list of words found in the input files. Cells 1 through 26 store the words 
   that start with an English alphabet and cell 27 stores words that dont 
   start with an English alphabet. Each cell has a list of words starting at 
   the alphabet in the position represented by the cell number: cell 1 has 
   words starting with an 'a' or 'A'. Words in the linked list are stored in 
   alphabetical order. Each word in turn is associated with a linked list of 
   files (along with the word's repetetion count in the said file) in which 
   the word appears.

   Once the database is created and stored in memory, it can be displayed 
   or saved into a file.
   

   DISPLAYING:
   The display program displays the index in which the word is stored along 
   with the list of files and the repetion count in each file.

   SAVING INTO FILE:
   Each word in the index is saved in a text file with the following format.
   
	#[INDEX_NO.,2 char]:[WORD_LENGTH, 2 char]:[WORD]:[FILE1_NAME_LENGTH, 2 char]:[FILENAME]:[WORD_COUNT]:...:[FILEN_NAME_LENGTH, 2 char]:[FILENAME]:[WORD_COUNT]#[nextline]

	Example:
	#24:04:you?:09:file1.txt:1:09:file2.txt:1#

   UPDATE INDEX:
   The backup file is read by the program and the hash table in the memory is updated with it's contents.

 */

/*
   The driver function to run the program.
 */
int main(int argc, char **argv) {

    //pointer to database index hash table.
    Word_List_Table *index_table = NULL;

    //superloop to ask for user choice.
    while(1) {
	printf("Select a choice:\n");
	printf("1. Create Database\n");
	printf("2. Display Database\n");
	printf("3. Search Database\n");
	printf("4. Save Database\n");
	printf("5. Update Database\n");
	printf("choice: ");

	int choice;
	scanf("%d", &choice);

	switch(choice) {

	    case 1:
		//check for input files.
		if(argc == 1) {
		    fprintf(stderr, "Input atleast 1 filename to index.\n");
		    return 1;
		}

		//validate arguments and collect the validation array.
		char *arg_val_array = validate_arguments(argc, argv);

		//create the inverted index database.
		index_table = create_database(argc, argv, arg_val_array);
		break;

	    case 2:
		//display database
		display_database(index_table);
		break;

	    case 3:
		if(index_table) {
		    //get the search word.
		    fprintf(stdout, "Enter the word to search: ");
		    char search_word[WORD_LENGTH_MAX];
		    scanf("%s", search_word);

		    //call the search function.
		    search_database(search_word, index_table);

		} else {
		    fprintf(stderr, "Database not created yet.\n");
		}
		break;

	    case 4:
		if(index_table) {
		    //save the database into a file.
		    save_database(index_table);
		} else {
		    fprintf(stderr, "Database not created yet.\n");
		}
		break;

	    case 5:
		if(!index_table) {
		    //allot memory for the index table.
		    index_table = create_table();

		    //update database into memory.
		    update_database(index_table);
		}

		break;

	    default:
		fprintf(stderr, "Invalid choice.\n");
		break;
	}

	//ask user choice to continue the program
	fprintf(stdout, "Continue? Y/n: ");
	while(getchar() != '\n');
	char cont;
	cont = getchar();

	if(!(cont == 'Y' || cont == 'y'))
	    break;
    }
}
