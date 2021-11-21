#ifndef HASH_TABLE_D_H
#define HASH_TABLE_D_H

struct Record;

/**
 * @brief A hash table that stores double values
 * 
 */
typedef struct HashTableD {
    int size;
    struct Record **records;
    double *(*get)(const struct HashTableD *, const char *);
    void (*set)(struct HashTableD *, char *, double);
    void (*ht_free)(struct HashTableD *);
} HashTableD;

HashTableD *init_ht_d(int size);

#endif
