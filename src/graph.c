#include "graph.h"
#include "coordinate.h"
#include <stdio.h>
#include <stdlib.h>

Graph init_graph(void) {
    Node *nodes;
    nodes = (Node *)calloc(5, sizeof(Node));
    if (nodes == NULL) {
        // dont know what to do if we get a NULL pointer
    }
    return (Graph){.nodes = nodes, .used = 0, .size = 5};
}

void add_node_to_graph(Graph *g, Node n) {
    if (g->used == g->size) {
        g->size += 5;
        Node *nodes = realloc(g->nodes, g->size * sizeof(Node));
        if (nodes == NULL) {
            // dont know what to do if we get a NULL pointer
        }
        g->nodes = nodes;
    }
    g->nodes[g->used++] = n;
}

void print_node(Node n) {
    printf("id: %d, name: %s, coords: ", n.id, n.name);
    print_coords(n.coord);
}

void print_graph(Graph g) {
    printf("--- Graph\n");
    printf("Size: %d\n", g.size);
    printf("Number of nodes: %d\n", g.used);
    printf("Nodes:\n");

    for (int i = 0; i < g.used; i++) {
        printf("\t - ");
        print_node(g.nodes[i]);
    }
}