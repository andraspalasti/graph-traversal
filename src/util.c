#include "util.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* This function splits a string into a number of parts
* and puts each part in the parts array
* WARNING: This function uses strtok so it modifies the original string
*/
void split(char *str, char *parts[], int num_of_splits, const char *sep) {
    // assert(num_of_splits > 0);
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
        print_error("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}

/*
* Removes all occurences of a specified char in a string
*/
void remove_chars(char *str, char char_to_remove) {
    int i, j;
    int len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == char_to_remove) {
            for (j = i; j < len; j++) {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }
}

/*
* Prints the message to the console in red and prefixis it with ERROR:
*/
__attribute__((format(printf, 1, 2))) void print_error(const char *format, ...) {
    va_list arg;
    va_start(arg, format);

    printf("\033[0;31mERROR: ");
    vprintf(format, arg);
    printf("\n\033[0m");

    va_end(arg);
}
