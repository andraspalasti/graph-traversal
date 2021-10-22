#ifndef UTIL_H_
#define UTIL_H_

/*
* This function splits a string into a number of parts
* and puts each part in the parts array
* WARNING: This function uses strtok so it modifies the original string
*/
void split(char *str, char *parts[], int num_of_splits, const char *sep);

/*
* Checks if the pointer is null
* if it is than the program exits with an error message
*/
void check_malloc(void *ptr);

#endif
