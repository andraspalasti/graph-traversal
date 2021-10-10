#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Searches for a node in the graph by name
* if found returns pointer to node else it returns a NULL pointer
*/
Node *search_for_node(Graph g, char *node_name) {
    for (size_t i = 0; i < g.used; i++) {
        if (strcmp(g.nodes[i]->name, node_name) == 0) {
            return g.nodes[i];
        }
    }
    return NULL;
}

void add_node(Graph *g, Node *n) {
    if (g->used == g->size) {
        g->nodes = (Node **)realloc(g->nodes, g->size + 5);
        assert(g->nodes != NULL);
        g->size += 5;
    }
    g->nodes[g->used++] = n;
}

void remove_node(Graph *g, size_t node_idx) {
    assert(node_idx < g->used);
    // track down adjacent nodes and delete the edges between them
    for (size_t i = 0; i < g->nodes[node_idx]->neighbors->used; i++) {
        size_t adjacent_n_idx = g->nodes[node_idx]->neighbors->adjacent_nodes[i]; // index of adjacent node
        assert(adjacent_n_idx < g->used);
        remove_node_idx(g->nodes[adjacent_n_idx]->neighbors, node_idx);
    }
    free_node(g->nodes[node_idx]);

    // if the node is not the last
    // than we need to shift the consecutive nodes to the left
    if (node_idx != g->used - 1) {
        memmove(g->nodes + node_idx, g->nodes + node_idx + 1, (g->used - node_idx - 1) * sizeof(Node *));
    }

    g->used--;

    if (g->used < g->size - 5) {
        g->nodes = (Node **)realloc(g->nodes, g->size - 5);
        assert(g->nodes != NULL);
        g->size -= 5;
    }
}

Graph *init_graph(void) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    assert(g != NULL);

    Node **nodes = (Node **)calloc(5, sizeof(Node *));
    assert(nodes != NULL);

    g->nodes = nodes;
    g->used = 0;
    g->size = 5;

    return g;
}

/*
* Frees the memory allocated by the graph
*/
void free_graph(Graph *g) {
    for (size_t i = 0; i < g->used; i++) {
        free_node(g->nodes[i]);
    }
    free(g->nodes);
    free(g);
}

/*
* Prints a graph to the console
*/
void print_graph(Graph g) {
    printf("--- GRAPH ---\n");
    printf("Size: %zu\n", g.size);
    printf("Number of nodes: %zu\n", g.used);
    printf("Nodes:\n");

    for (size_t i = 0; i < g.used; i++) {
        printf("---\n");
        print_node(*(g.nodes[i]));
    }
}
