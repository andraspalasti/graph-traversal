#include "hash_table.h"
#include "../include/debugmalloc.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    char *key;
    void *val;
    struct Record *next;
} Record;

static struct Record *init_record(char *key, void *val);
static void free_record(struct Record *r);

/**
 * @brief Instantiates a HashTable
 * ATTENTION: You have to be very carefull with the hash table because
 * it uses void pointers to be able to use it with any type.
 * The hash table saves the pointer and not the value of the variable so if
 * the variable will go out of scope the hash table will point to a not allocated memory 
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

    return hash_table;
}

/**
 * @brief If it finds the specified key in the HashTable
 * it overrides its value with the specified
 * else it inserts it in
 * 
 * @param ht The hash table to insert in
 * @param key The key to search for
 * @param val The data to insert
 */
void ht_set_value(HashTable *ht, char *key, void *val) {
    int idx = hash(key) % ht->size;
    Record *prev_r = NULL;
    Record *r = ht->records[idx];
    while (r != NULL && strcmp(key, r->key) != 0) {
        prev_r = r;
        r = r->next;
    }

    // the key is not in the table
    if (r == NULL) {
        Record *new_data = init_record(key, val);
        // its the start of the list
        if (prev_r == NULL)
            ht->records[idx] = new_data;
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
 * @param ht The hash table to search in
 * @param key The key to search for
 * @return void* The pointer to the value
 */
void *ht_get_value(const HashTable *ht, const char *key) {
    int idx = hash(key) % ht->size;
    Record *r = ht->records[idx];
    while (r != NULL && strcmp(key, r->key) != 0) {
        r = r->next;
    }

    return r == NULL ? NULL : r->val;
}

/**
 * @brief Frees the specified HashTable
 * ATTENTION: it does not free the values used in the table
 * 
 * @param ht The hash table to free
 */
void free_ht(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {

        // we need to free all records in the row
        Record *r = ht->records[i];
        while (r != NULL) {
            Record *tmp = r->next;
            free_record(r);
            r = tmp;
        }
    }

    free(ht->records);
    free(ht);
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

    r->key = strdup(key);
    check_malloc(r->key);
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
