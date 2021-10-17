#ifndef NEIGHBOUR_H_
#define NEIGHBOUR_H_

#include "node.h"

typedef struct Neighbour {
    struct Node *node;
    struct Neighbour *next_node;
} Neighbour;

/*
* Instantiates a new neighbour
*/
Neighbour *init_neighbour(struct Node *n);

/*
* Frees the memory allocated by the neighbour
*/
void free_neighbour(Neighbour *neighbour);

/*
* Prints a neighbour to the console
*/
void print_neighbour(Neighbour *neighbour);

#endif
