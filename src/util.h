#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

void split(char *str, char *parts[], int num_of_splits, const char *sep);

char *trim(char *str);

int hash(const char *key);

void check_malloc(void *ptr);

void remove_chars(char *str, char char_to_remove);

void read_str(char *str, int len);

void print_error(const char *format, ...);

#endif
