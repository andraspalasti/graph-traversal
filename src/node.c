#include "node.h"
#include "neighbour.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Adds a neighbour to the node at the specified position
* You can insert to the end with pos = -1
* @param pos starts at 0 
*/
void add_neighbour_at(int pos, Node *n, Node *adjacent_node) {
    Neighbour *neighbour = init_neighbour(adjacent_node);
    assert(neighbour != NULL);

    // if neighbour list is empty
    if (n->neighbours == NULL) {
        n->neighbours = neighbour;
        return;
    }

    int idx = 0;
    Neighbour *prev = NULL;
    Neighbour *cur = n->neighbours;

    // walk through list until pos or end is reached
    while (cur != NULL && idx != pos) {
        idx++;
        prev = cur;
        cur = cur->next_node;
    };

    // if you want to insert to the begining
    if (prev == NULL) {
        neighbour->next_node = cur;
        n->neighbours = neighbour;
        return;
    }

    // if you want to insert to the end
    if (cur == NULL) {
        prev->next_node = neighbour;
        return;
    }

    // if you want to insert to the middle
    prev->next_node = neighbour;
    neighbour->next_node = cur;
}

/*
* Instantiates a new node
*/
Node *init_node(char *name, Coordinates coords) {
    assert(strlen(name) < 21);

    Node *n = (Node *)malloc(sizeof(Node));
    assert(n != NULL);

    strcpy(n->name, name);
    n->coords = coords;
    n->neighbours = NULL;

    return n;
}

/*
* Frees the memory allocated by the node
*/
void free_node(Node *n) {
    free_neighbour(n->neighbours);
    free(n);
}

/*
* Prints a node to the console
*/
void print_node(Node n) {
    printf("name: %s, coords: ", n.name);
    print_coords(n.coords);

    printf("Neighbours: ");
    print_neighbour(n.neighbours);
}
