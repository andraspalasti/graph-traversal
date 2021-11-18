#ifndef HASH_TABLE_N_H
#define HASH_TABLE_N_H

#include "../node.h"
#include <stdbool.h>

struct Record;

/**
 * @brief A hash table that stores nodes
 * 
 */
typedef struct HashTableN {
    int size;
    struct Record **records;
    Node *(*get)(const struct HashTableN *, const char *);
    void (*set)(struct HashTableN *, char *, Node *);
    void (*free_table)(struct HashTableN *);
} HashTableN;

HashTableN *init_hash_table_n(int size);

#endif
