#ifndef GRAPH_H_
#define GRAPH_H_

#include "node.h"

typedef struct Graph {
    Node **nodes;
    int used, capacity;
} Graph;

/*
* Finds the node specified by the name
* if found returns a pointer to the node
* else it returns a null pointer
*/
Node *find_node(const Graph *g, const char *name);

/*
* Adds a node to the graph
* It inserts the node to the end
*/
void add_node(Graph *g, Node *n);

/*
* Finds the node specified by the name and deletes it
*/
void delete_node(Graph *g, Node *n);

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
void print_graph(const Graph *g);

#endif
