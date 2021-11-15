#ifndef QUEUE_H
#define QUEUE_H

#include "list_node.h"

typedef struct Queue {
    ListNode *head;
    ListNode *last; // the pointer to the last list node in the queue
} Queue;

Queue *init_queue();

void enqueue(Queue *q, Node *n);

void dequeue(Queue *q, Node *n);

void free_queue(Queue *q);

#endif
