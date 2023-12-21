#include <stdio.h>
#include "argument.h"
#include "create_index.h"
#include "word_list_table.h"
#include "allocator.h"

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
	printf("3. Exit\n");
	printf("choice: ");

	int choice;
	scanf("%d", &choice);

	switch(choice) {
	    case 1:
		    //create the inverted index database.
		    index_table = create_database(argc, argv, arg_val_array);
		    break;
	    case 2:
		    if(index_table) {
		    //display database
		    print_table(index_table);
		    } else {
			fprintf(stderr, "Index not yet created.\n");
		    }
		    break;
	    case 3:
		    //exit program.
		    free_all_memory();
		    return 0;
	    default:
		fprintf(stderr, "Invalid choice.\n");
		break;
	}
    }
}
