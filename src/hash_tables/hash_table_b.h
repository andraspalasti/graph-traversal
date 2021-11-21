#ifndef HASH_TABLE_B_H
#define HASH_TABLE_B_H

#include <stdbool.h>

struct Record;

/**
 * @brief A hash table that stores bool values
 * 
 */
typedef struct HashTableB {
    int size;
    struct Record **records;
    bool *(*get)(const struct HashTableB *, const char *);
    void (*set)(struct HashTableB *, char *, bool);
    void (*ht_free)(struct HashTableB *);
} HashTableB;

HashTableB *init_ht_b(int size);

#endif
