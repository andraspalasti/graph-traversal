#ifndef GRAPH_H_
#define GRAPH_H_

#include "node.h"

typedef struct Graph {
    Node **nodes;
    size_t used, size;
} Graph;

/*
* Searches for a node in the graph by name
* if found returns pointer to node else it returns a NULL pointer
*/
Node *search_for_node(Graph g, char *node_name);

/*
* Adds a node to a graph
*/
void add_node(Graph *g, Node *n);

/*
* Removes a node from the graph
*/
void remove_node(Graph *g, size_t node_idx);

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
