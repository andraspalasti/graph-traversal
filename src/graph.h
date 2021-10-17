#ifndef GRAPH_H_
#define GRAPH_H_

#include "node.h"

typedef struct Graph {
    Node *node;
    struct Graph *next_node;
} Graph;

// /*
// * Adds a node to a graph
// */
// void add_node(Graph *g, Node *n);

// /*
// * Removes a node from the graph
// */
// void remove_node(Graph *g, size_t node_idx);

/*
* Instantiates a new graph
*/
Graph *init_graph(void);

/*
* Frees the memory allocated by the graph
*/
void free_graph(Graph *g);

/*
* Prints a graph to the console
*/
void print_graph(Graph g);

#endif
