#ifndef NODE_H_
#define NODE_H_

#include "coordinate.h"
#include "edges.h"

#define MAX_NAME_LENGTH 11

typedef struct Node {
    char name[MAX_NAME_LENGTH];
    Coordinate coord;
    ArrayOfEdges neighbors;
} Node;

/*
* Adds an edge to a node
*/
void add_edge_to_node(Node n, Edge e);

/*
* Instantiates a new node
*/
Node *init_node(char *name, Coordinate coord);

/*
* Prints a node to the console
*/
void print_node(Node n);

#endif