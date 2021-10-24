#ifndef NODE_H_
#define NODE_H_

#include "coordinates.h"
#include "list_node.h"

typedef struct Node {
    char *name;
    Coordinates coords;
    struct ListNode *neighbours;
} Node;

/*
* Adds a neighbour to the node at the specified position
* @param pos starts at 0, you can insert to the end with pos = -1
*/
void add_neighbour_at(int pos, Node *n, Node *adjacent_node);

/*
* Removes the neighbour from the specified node
*/
void remove_neighbour(Node *n, Node *neighbour);

/*
* Instantiates a new node
*/
Node *init_node(const char *name, Coordinates coords);

/*
* Frees the memory allocated by the node
*/
void free_node(Node *n);

/*
* Prints a node to the console
*/
void print_node(const Node *n);

#endif
