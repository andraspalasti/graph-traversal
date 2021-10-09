#include "node.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *init_node(char *name, Coordinates coords) {
    Node *n = (Node *)malloc(sizeof(Node));
    assert(n != NULL);
    Edges *neighbors = init_edges();
    assert(neighbors != NULL);
    n->neighbors = neighbors;

    n->coords = coords;
    n->name = strdup(name);
    assert(n->name != NULL);

    return n;
}

void free_node(Node *n) {
    free(n->name);
    free_edges(n->neighbors);
    free(n);
}

void print_node(Node n) {
    printf("name: %s, coords: ", n.name);
    print_coords(n.coords);
    printf("edges: ");
    print_edges(*(n.neighbors));
}
