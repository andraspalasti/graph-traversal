#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_edge_to_node(Node n, Edge e) {
    add_edge(&n.neighbors, e);
}

Node *init_node(char *name, Coordinate coord) {
    Node *n = (Node *)malloc(sizeof(Node));
    strcpy(n->name, name);
    n->coord = coord;
    n->neighbors = init_edges();
    return n;
}

void print_node(Node n) {
    printf("name: %s, coords: ", n.name);
    print_coords(n.coord);
    printf("edges: ");
    print_edges(n.neighbors);
}