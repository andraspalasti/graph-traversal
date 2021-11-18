#ifndef HASH_TABLE_D_H
#define HASH_TABLE_D_H

#include <stdbool.h>

struct Record;

/**
 * @brief A hash table that stores double values
 */
typedef struct HashTableD {
    int size;
    struct Record **records;
    double *(*get)(const struct HashTableD *, const char *);
    void (*set)(struct HashTableD *, char *, double);
    void (*free_table)(struct HashTableD *);
} HashTableD;

HashTableD *init_hash_table_b(int size);

#endif
