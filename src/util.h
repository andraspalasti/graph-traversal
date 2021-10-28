#ifndef UTIL_H
#define UTIL_H

void split(char *str, char *parts[], int num_of_splits, const char *sep);

void check_malloc(void *ptr);

void remove_chars(char *str, char char_to_remove);

void print_error(const char *format, ...);

#endif
