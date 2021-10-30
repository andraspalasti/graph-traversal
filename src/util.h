#ifndef UTIL_H
#define UTIL_H

#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"

void **init_matrix(int rows, int cols, size_t size);

void free_matrix(void **matrix);

void split(char *str, char *parts[], int num_of_splits, const char *sep);

void check_malloc(void *ptr);

void remove_chars(char *str, char char_to_remove);

void print_error(const char *format, ...);

#endif
