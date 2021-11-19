#include "graph.h"
#include "../include/debugmalloc.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Searches for the specified node by name
 * 
 * @param g The graph to search in
 * @param name The node's name to search for
 * @return Node* returns null pointer if it can not find node
 */
Node *find_node(const Graph *g, const char *name) {
    for (int i = 0; i < g->used; i++) {
        if (strcmp(g->nodes[i]->name, name) == 0) {
            return g->nodes[i];
        }
    }
    return NULL;
}

/**
 * @brief Adds node to the end of the graph.
 * It has a side effect:
 * it sets the node's idx field to the corresponding index
 * 
 * @param g Graph
 * @param n Node to add to graph
 */
void add_node_to_graph(Graph *g, Node *n) {
    // the allocated array is full
    if (g->used == g->capacity) {
        g->nodes = realloc(g->nodes, g->capacity + 10);
        check_malloc(g->nodes);
        g->capacity += 10;
    }
    g->nodes[g->used] = n;
    g->used += 1;
}

/**
 * @brief Deletes the specified node from the graph.
 * It also deletes all connections to this node
 * 
 * @param g Graph
 * @param n Node to delete
 */
void delete_node_from_graph(Graph *g, Node *n) {
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
        remove_neighbour(g->nodes[j], n);
    }
    g->used -= 1;
    if (g->used < g->capacity - 10) {
        g->nodes = realloc(g->nodes, g->capacity - 10);
        check_malloc(g->nodes);
        g->capacity -= 10;
    }
}

/**
 * @brief Instantiates a graph.
 * This allocates memory on the heap, 
 * you need to free this with the free_graph function
 * 
 * @return Graph* pointer to the allocated graph
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

/**
 * @brief Frees the memory allocated by the graph
 * and all of it's nodes
 * 
 * @param g pointer to the graph
 */
void free_graph(Graph *g) {
    for (int i = 0; i < g->used; i++) {
        free_node(g->nodes[i]);
    }
    free(g->nodes);
    free(g);
}

/**
 * @brief Prints the graph to the console
 * 
 * @param g pointer to the graph
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
