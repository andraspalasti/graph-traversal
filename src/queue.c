#include "queue.h"
#include "util.h"
#include <stdlib.h>

/**
 * @brief Instantiates a new queue
 * 
 * @return Queue* The pointer to the new queue
 */
Queue *init_queue() {
    Queue *q = malloc(sizeof(Queue));
    check_malloc(q);

    q->head = NULL;
    q->last = NULL;

    return q;
}

/**
 * @brief Inserts a node to the Queues end
 * 
 * @param q The queue to insert the node in
 * @param n The node to insert
 */
void enqueue(Queue *q, Node *n) {
    ListNode *new_ln = init_list_node(n);
    if (q->head == NULL) {
        q->head = new_ln;
        q->last = new_ln;
        return;
    }

    q->last->next_node = new_ln;
    q->last = new_ln;
}

/**
 * @brief It removes the specified node from the queue
 * 
 * @param q The queue to remove the node from
 * @param n The node to remove
 */
void dequeue(Queue *q, Node *n) {
    ListNode *prev = NULL;
    ListNode *cur_ln = q->head;
    while (cur_ln != NULL && cur_ln->node != n) {
        prev = cur_ln;
        cur_ln = cur_ln->next_node;
    }

    // if we did not find it
    if (cur_ln == NULL)
        return;

    // if its the first element
    if (prev == NULL) {
        q->head = cur_ln->next_node;
        // check if it was the first and last element
        q->last = cur_ln->next_node == NULL ? NULL : q->last;
        free(cur_ln);
        return;
    }

    // if its the last element
    if (cur_ln->next_node == NULL) {
        prev->next_node = NULL;
        q->last = prev;
        free(cur_ln);
        return;
    }

    // if its in the middle
    prev->next_node = cur_ln->next_node;
    free(cur_ln);
}

/**
 * @brief Frees the allocated Queue
 * 
 * @param q The queue to free
 */
void free_queue(Queue *q) {
    free_list_node(q->head);
    free(q);
}
