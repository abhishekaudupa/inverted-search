#include <stdio.h>
#include "argument.h"
#include "allocator.h"

int main(int argc, char **argv) {

    for(int i = 0; i < argc; ++i)
	printf("%s\n", argv[i]);

    //validate arguments and collect the validation array.
    char *arg_val = validate_arguments(argc, argv);

    for(int i = 0; i < argc; ++i) {
	if(arg_val[i])
	    printf("Valid:   %s\n", argv[i]);
	else
	    printf("Invalid: %s\n", argv[i]);
    }

    free_memory(arg_val);
    free_all_memory();
}

