#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"

typedef struct Graph {
    Node **nodes;
    int used, capacity;
} Graph;

Node *find_node(const Graph *g, const char *name);

void add_node_to_graph(Graph *g, Node *n);

void delete_node_from_graph(Graph *g, Node *n);

Graph *init_graph(void);

void free_graph(Graph *g);

void print_graph(const Graph *g);

#endif
