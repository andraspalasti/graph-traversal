#ifndef GRAPH_H_
#define GRAPH_H_

#include "node.h"

typedef struct Graph {
    Node **nodes;
    size_t used, size;
} Graph;

// /*
// * Reads a graph from a csv file
// * The csv should look like this:
// * AA;10;10;""
// * OA;-678;-166;""
// * FD;31;392;""
// */
// Graph *read_graph_from_file(char *fpath);

// /*
// * Reads a graph from a csv file
// * The csv should look like this:
// * AA;10;10;""
// * OA;-678;-166;""
// * FD;31;392;""
// */
// void *read_edges_from_file_to_graph(char *fname, Graph *g);

// /*
// * Adds a node to a graph
// */
// void add_node_to_graph(Graph *g, Node n);

/*
* Instantiates a new graph
*/
Graph *init_graph(void);

/*
* Frees the memory allocated by the graph
*/
Graph *free_graph(void);

/*
* Prints a graph to the console
*/
void print_graph(Graph g);

#endif
