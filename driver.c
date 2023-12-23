#include <stdio.h>
#include "argument.h"
#include "create_index.h"
#include "word_list_table.h"
#include "allocator.h"
#include "display_index.h"
#include "search_index.h"

int main(int argc, char **argv) {

    //check for input files.
    if(argc == 1) {
	fprintf(stderr, "Input atleast 1 filename to index.\n");
	return 1;
    }

    //validate arguments and collect the validation array.
    char *arg_val_array = validate_arguments(argc, argv);

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
		} else {
		    fprintf(stderr, "Database not created yet.\n");
		}
		break;

	    case 5:
		//update
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
