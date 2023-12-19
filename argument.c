#include "argument.h"
#include "allocator.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

char *validate_arguments(const int argc, char **argv) {
    //design time check
    assert(argv);
    assert(*argv);

    //argument validity array.
    char *result = get_memory(argc * sizeof(*result));
    if(!result)
	return NULL;

    result[0] = 0;

    //check if files are .txt
    for(int i = 0; i < argc; ++i) {
	//argument string length (filename length).
	int filename_len = strlen(argv[i]);

	//check if file extension is ".txt"
	if(argv[i][filename_len - 1] == 't'
		&& argv[i][filename_len - 2] == 'x'
		&& argv[i][filename_len - 3] == 't'
		&& argv[i][filename_len - 4] == '.')
	    result[i] = 1;
	else
	    result[i] = 0;
    }

    //check duplicates.
    for(int i = 0; i < argc - 1; ++i) {
	//check duplicates of ".txt" only.
	if(result[i]) {
	    for(int j = i + 1; j < argc; ++j) {
		if(strcmp(argv[i], argv[j]) == 0) {
		    result[j] = 0;
		}
	    }
	}
    }

    return result;
}
