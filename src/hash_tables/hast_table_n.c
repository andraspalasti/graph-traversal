#include "../../include/debugmalloc.h"
#include "../util.h"
#include "hash.h"
#include "hash_table_n.h"
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    char *key;
    Node *node;
    struct Record *next;
} Record;

HashTableN *init_hash_table_n(int size);
Node *get(const HashTableN *self, const char *key);
void set(HashTableN *self, char *key, Node *n);
void free_hash_table(HashTableN *self);

Record *init_record(char *key, Node *n);
void free_record(Record *r);

/**
 * @brief Instantiates a hash table struct with default values
 * 
 * @param size The size of the table
 * @return HashTableN* The pointer to the newly created hash table
 */
HashTableN *init_hash_table_n(int size) {
    HashTableN *hash_table = malloc(sizeof(HashTableN));
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
 * @brief Frees the memory allocated by the hash table
 * 
 * @param self The hash table to free
 */
void free_hash_table(HashTableN *self) {
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
 * @brief It searches for the value stored
 * by the specified key
 * 
 * @param self The hash table to search in
 * @param key The key to search for
 * @return Node* The found node if we did not find the key it will be a NULL pointer
 */
Node *get(const HashTableN *self, const char *key) {
    int idx = hash(key) % self->size;
    Record *td = self->records[idx];
    while (td != NULL && strcmp(key, td->key) != 0) {
        td = td->next;
    }

    return td == NULL ? NULL : td->node;
}

/**
 * @brief If the key is already in the table it overrides its value
 * else it inserts it with the specified node
 * 
 * @param self The hash table to insert the node in
 * @param key The key to insert the node with
 * @param n The node to insert
 */
void set(HashTableN *self, char *key, Node *n) {
    int idx = hash(key) % self->size;
    Record *prev_td = NULL;
    Record *r = self->records[idx];
    while (r != NULL && strcmp(key, r->key) != 0) {
        prev_td = r;
        r = r->next;
    }

    // the key is not in the table
    if (r == NULL) {
        Record *new_data = init_record(key, n);
        // its the start of the list
        if (prev_td == NULL)
            self->records[idx] = new_data;
        else
            prev_td->next = new_data;
        return;
    }

    // if we found the key we change its corresponding value
    r->node = n;
}

/**
 * @brief Instantiates a record struct
 * 
 * @param key The key to use
 * @param n The node to store
 * @return Record* 
 */
Record *init_record(char *key, Node *n) {
    Record *r = malloc(sizeof(Record));
    check_malloc(r);

    // dont know if we should allocate memory for the key in the heap
    // leave it commented for now
    // r->key = strdup(key); // need to free key
    // check_malloc(r->key);
    r->key = key;
    r->node = n;
    r->next = NULL;
    return r;
}

/**
 * @brief Frees the record
 * 
 * @param td The record to free
 */
void free_record(Record *r) {
    // free(td->key);
    free(r);
}
