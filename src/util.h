#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdlib.h>

#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"

bool **init_bool_matrix(int rows, int cols);

void free_bool_matrix(bool **matrix);

void split(char *str, char *parts[], int num_of_splits, const char *sep);

char *trim(char *str);

void check_malloc(void *ptr);

void remove_chars(char *str, char char_to_remove);

void print_error(const char *format, ...);

#endif
