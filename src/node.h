#ifndef NODE_H_
#define NODE_H_

#include "coordinates.h"
#include "neighbour.h"

typedef struct Node {
    char name[21];
    Coordinates coords;
    struct Neighbour *neighbours;
} Node;

/*
* Adds a neighbour to the node at the specified position
* @param pos starts at 0, you can insert to the end with pos = -1
*/
void add_neighbour_at(int pos, Node *n, Node *adjacent_node);

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
