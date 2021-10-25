#ifndef PATH_FINDING_H
#define PATH_FINDING_H

#include "graph.h"

typedef struct ListNode Queue;

typedef struct ListNode Path;

Path *find_path(Graph *g, Node *src, Node *target);

void load_path(Path **p, Node **prev, Node *end);

Node *min_dist_node(Queue *q, const double *dist);

void free_path(Path *p);

void print_path(Path *p);

void enqueue(int pos, Queue **head, Queue *q);

void remove_from_queue(Queue **q, Node *n);

Queue *init_queue(Node *n);

void free_queue(Queue *q);

#endif
