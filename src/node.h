#ifndef NODE_H_
#define NODE_H_

#include "coordinates.h"
#include "edges.h"

typedef struct Node {
    char *name;
    Coordinates coords;
    Edges *neighbors;
} Node;

/*
* Instantiates a new node
*/
Node *init_node(char *name, Coordinates coords);

/*
* Frees the memory allocated by the node
*/
void free_node(Node *n);

/*
* Prints a node to the console
*/
void print_node(Node n);

#endif
