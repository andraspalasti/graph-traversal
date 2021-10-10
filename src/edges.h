#ifndef EDGES_H_
#define EDGES_H_

#include <stdlib.h>

typedef struct Edges {
    size_t *adjacent_nodes; // array that stores the index of adjacent nodes
    size_t used, size;
} Edges;

/*
* Adds a node's index to the list of edges
*/
void add_node_idx(Edges *e, size_t node_index);

/*
* Searches for the specified value if found it deletes it
* than shifts the values left
*/
void remove_node_idx(Edges *e, size_t node_index);

/*
* Instantiates a new array of edges
*/
Edges *init_edges(void);

/*
* Frees memory allocated by edges
*/
void free_edges(Edges *e);

/*
* Prints an edge to the console
*/
void print_edges(Edges e);

#endif
