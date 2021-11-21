#include "hash_table.h"
#include "../../include/debugmalloc.h"
#include "../util.h"
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    char *key;
    void *val;
    struct Record *next;
} Record;

static struct Record *init_record(char *key, void *val);
static void free_record(struct Record *r);
static void set_value(HashTable *self, char *key, void *val);
static void free_ht(HashTable *self);
static void **get_value(const HashTable *self, const char *key);

/**
 * @brief Instantiates a HashTable
 * 
 * @param size The size of the table
 * @return HashTable* The pointer to the newly created hash table
 */
HashTable *init_ht(int size) {
    HashTable *hash_table = malloc(sizeof(HashTable));
    check_malloc(hash_table);

    // we use calloc so the array will be full of NULL pointers
    Record **data = calloc(size, sizeof(Record *));
    check_malloc(data);

    hash_table->size = size;
    hash_table->records = data;
    hash_table->get = get_value;
    hash_table->set = set_value;
    hash_table->ht_free = free_ht;

    return hash_table;
}

/**
 * @brief If it finds the specified key in the HashTable
 * than it overrides its value pointer
 * else it inserts the specified pointer in
 * 
 * @param self The hash table to insert in
 * @param key The key to search for
 * @param val The value that you want to insert
 */
static void set_value(HashTable *self, char *key, void *val) {
    int idx = hash(key) % self->size;
    Record *prev_r = NULL;
    Record *r = self->records[idx];
    while (r != NULL && strcmp(key, r->key) != 0) {
        prev_r = r;
        r = r->next;
    }

    // the key is not in the table
    if (r == NULL) {
        Record *new_data = init_record(key, val);
        // its the start of the list
        if (prev_r == NULL)
            self->records[idx] = new_data;
        else
            prev_r->next = new_data;
        return;
    }

    // if we found the key we change its corresponding value
    r->val = val;
}

/**
 * @brief It searches for the specified key in the HashTable
 * If the key is found than it returns a pointer to its value
 * else it returns a NULL pointer
 * 
 * @param self The hash table to search in
 * @param key The key to search for
 * @return void* The pointer to the value
 */
static void **get_value(const HashTable *self, const char *key) {
    int idx = hash(key) % self->size;
    Record *r = self->records[idx];
    while (r != NULL && strcmp(key, r->key) != 0) {
        r = r->next;
    }

    return r == NULL ? NULL : &(r->val);
}

/**
 * @brief Frees the specified HashTable
 * ATTENTION: it does not free the values used in the table
 * 
 * @param self The hash table to free
 */
static void free_ht(HashTable *self) {
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
static Record *init_record(char *key, void *val) {
    Record *r = malloc(sizeof(Record));
    check_malloc(r);

    r->key = malloc(strlen(key) + 1);
    check_malloc(r->key);
    strcpy(r->key, key);
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
    free(r->key);
    free(r);
}
