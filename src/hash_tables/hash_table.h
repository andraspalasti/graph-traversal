#ifndef HASH_TABLE_H
#define HASH_TABLE_H

struct Record;

typedef struct HashTable {
    int size;
    struct Record **records;
    void **(*get)(const struct HashTable *, const char *);
    void (*set)(struct HashTable *, char *, void *);
    void (*ht_free)(struct HashTable *);
} HashTable;

HashTable *init_ht(int size);

#endif
