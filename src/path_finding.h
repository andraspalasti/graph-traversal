#ifndef PATH_FINDING_H
#define PATH_FINDING_H

#include "graph.h"
#include "queue.h"

typedef struct ListNode Path;

Path *find_path(Graph *g, Node *src, Node *target);

void free_path(Path *p);

void print_path(Path *p);

#endif
