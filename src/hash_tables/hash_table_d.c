#include "hash_table_d.h"
#include "../../include/debugmalloc.h"
#include "../util.h"
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    char *key;
    double val;
    struct Record *next;
} Record;

static void set(HashTableD *self, char *key, double n);
static double *get(const HashTableD *self, const char *key);
static void free_hash_table(HashTableD *self);
static struct Record *init_record(char *key, double val);
static void free_record(struct Record *r);

/**
 * @brief Instantiates a hash table struct with default values
 * 
 * @param size The size of the table
 * @return HashTableD* The pointer to the newly created hash table
 */
HashTableD *init_hash_table_d(int size) {
    HashTableD *hash_table = malloc(sizeof(HashTableD));
    check_malloc(hash_table);

    // we use calloc so the array will be full of NULL pointers
    Record **data = calloc(size, sizeof(Record *));
    check_malloc(data);

    hash_table->size = size;
    hash_table->records = data;
    hash_table->get = get;
    hash_table->set = set;
    hash_table->free_table = free_hash_table;

    return hash_table;
}

/**
 * @brief It searches for the value stored
 * by the specified key
 * 
 * @param self The hash table to search in
 * @param key The key to search for
 * @return double* The found value if we did not find the key it will be a NULL pointer
 */
static double *get(const HashTableD *self, const char *key) {
    int idx = hash(key) % self->size;
    Record *td = self->records[idx];
    while (td != NULL && strcmp(key, td->key) != 0) {
        td = td->next;
    }

    return td == NULL ? NULL : &(td->val);
}

/**
 * @brief If the key is already in the table it overrides its value
 * else it inserts it with the specified val
 * 
 * @param self The hash table to insert the val in
 * @param key The key to insert the val with
 * @param val The value to insert
 */
static void set(HashTableD *self, char *key, double val) {
    int idx = hash(key) % self->size;
    Record *prev_td = NULL;
    Record *r = self->records[idx];
    while (r != NULL && strcmp(key, r->key) != 0) {
        prev_td = r;
        r = r->next;
    }

    // the key is not in the table
    if (r == NULL) {
        Record *new_data = init_record(key, val);
        // its the start of the list
        if (prev_td == NULL)
            self->records[idx] = new_data;
        else
            prev_td->next = new_data;
        return;
    }

    // if we found the key we change its corresponding value
    r->val = val;
}

/**
 * @brief Frees the memory allocated by the hash table
 * 
 * @param self The hash table to free
 */
static void free_hash_table(HashTableD *self) {
    for (int i = 0; i < self->size; i++) {

        // we need to free all records in the row
        Record *r = self->records[i];
        while (r != NULL) {
            Record *tmp = r->next;
            free_record(r);
            r = tmp;
        }
    }

    free(self->records);
    free(self);
}

/**
 * @brief Instantiates a record struct
 * 
 * @param key The key to use
 * @param val The value to store
 * @return Record* 
 */
static Record *init_record(char *key, double val) {
    Record *r = malloc(sizeof(Record));
    check_malloc(r);

    r->key = key;
    r->val = val;
    r->next = NULL;
    return r;
}

/**
 * @brief Frees the record
 * 
 * @param td The record to free
 */
static void free_record(Record *r) {
    free(r);
}
