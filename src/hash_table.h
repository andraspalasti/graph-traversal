#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

struct Record;

typedef struct HashTable {
    int size;
    struct Record **records;
} HashTable;

HashTable *init_ht(int size);

void set_value_ptr(HashTable *ht, char *key, void *val);

void *ht_get_value(const HashTable *ht, const char *key);

void ht_free(HashTable *ht);

#endif
