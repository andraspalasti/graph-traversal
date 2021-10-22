#include "util.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* This function splits a string into a number of parts
* and puts each part in the parts array
* WARNING: This function uses strtok so it modifies the original string
*/
void split(char *str, char *parts[], int num_of_splits, const char *sep) {
    assert(num_of_splits > 0);
    parts[0] = strtok(str, sep);
    for (int i = 1; i < num_of_splits; i++) {
        parts[i] = strtok(NULL, sep);
    }
}

/*
* Checks if the pointer is null
* if it is than the program exits with an error message
*/
void check_malloc(void *ptr) {
    if (ptr == NULL) {
        printf("ERROR: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
}
