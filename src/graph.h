#ifndef GRAPH_H_
#define GRAPH_H_

#include "node.h"

typedef struct Graph {
    ListNode *nodes;
} Graph;

/*
* Adds a node to the graph at the specified position
* @param pos starts at 0, you can insert to the end with pos = -1
*/
void add_node_at(int pos, Graph *g, Node *n);

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
void print_graph(Graph *g);

#endif
