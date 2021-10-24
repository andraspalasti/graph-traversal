#include "graph.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Finds the node specified by the name
* if found returns a pointer to the node
* else it returns a null pointer
*/
Node *find_node(const Graph *g, const char *name) {
    for (int i = 0; i < g->used; i++) {
        if (strcmp(g->nodes[i]->name, name) == 0) {
            return g->nodes[i];
        }
    }
    return NULL;
}

/*
* Adds a node to the graph
* It inserts the node to the end
*/
void add_node(Graph *g, Node *n) {
    // the allocated array is full
    if (g->used == g->capacity) {
        g->nodes = realloc(g->nodes, g->capacity + 10);
        check_malloc(g->nodes);
        g->capacity += 10;
    }
    g->nodes[g->used] = n;
    n->idx = g->used;
    g->used += 1;
}

/*
* Finds the node specified by the name and deletes it
*/
void delete_node(Graph *g, Node *n) {
    int i = 0;
    while (i < g->used && g->nodes[i] != n) {
        remove_neighbour(g->nodes[i], n);
        i++;
    }
    // we did not find it
    if (i == g->used)
        return;

    free_node(g->nodes[i]);
    // shift following elements left
    for (int j = i; j < g->used - 1; j++) {
        g->nodes[j] = g->nodes[j + 1];
        g->nodes[j]->idx -= 1;
        remove_neighbour(g->nodes[j], n);
    }
    g->used -= 1;
    if (g->used < g->capacity - 10) {
        g->nodes = realloc(g->nodes, g->capacity - 10);
        check_malloc(g->nodes);
        g->capacity -= 10;
    }
}

/*
* Instantiates a new graph
*/
Graph *init_graph(void) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    check_malloc(g);
    g->nodes = (Node **)malloc(10 * sizeof(Node *));
    if (g->nodes == NULL) {
        free(g);
        print_error("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    g->used = 0;
    g->capacity = 10;
    return g;
}

/*
* Frees the memory allocated by the graph
*/
void free_graph(Graph *g) {
    for (int i = 0; i < g->used; i++) {
        free_node(g->nodes[i]);
    }
    free(g->nodes);
    free(g);
}

/*
* Prints a graph to the console
*/
void print_graph(const Graph *g) {
    if (g->used == 0) {
        printf("There are no nodes in your graph\n");
        return;
    }

    printf("--- GRAPH ---\n");
    for (int i = 0; i < g->used; i++) {
        print_node(g->nodes[i]);
        if (i != g->used - 1)
            printf("---\n");
    }
}
