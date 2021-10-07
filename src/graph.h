#ifndef GRAPH_H_
#define GRAPH_H_

#include "node.h"

typedef struct Graph {
    Node *nodes; // array
    int used;
    int size;
} Graph;

/*
* Reads a graph from a csv file
* The csv should look like this:
* AA;10;10
* OA;-678;-166
* FD;31;392
*/
Graph *read_graph_from_file(char *fname);

/*
* Adds a node to a graph
*/
void add_node_to_graph(Graph *g, Node n);

/*
* Instantiates a new graph
*/
Graph *init_graph(void);

/*
* Prints a graph to the console
*/
void print_graph(Graph g);

#endif