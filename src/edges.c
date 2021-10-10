#include "edges.h"
#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_node_idx(Edges *e, size_t node_index) {
    if (e->used == e->size) {
        e->adjacent_nodes = (size_t *)realloc(e->adjacent_nodes, e->size + 5);
        assert(e->adjacent_nodes != NULL);
        e->size += 5;
    }
    e->adjacent_nodes[e->used++] = node_index;
}

void remove_node_idx(Edges *e, size_t node_index) {
    size_t i = 0;
    while (e->adjacent_nodes[i] != node_index && i < e->used)
        i++;
    if (i >= e->used)
        return;

    // check if it is the last element
    // because if it is we dont have anything to shift
    if (i == e->used - 1) {
        e->adjacent_nodes[i] = 0;
    } else {
        // shift array left to occupy free space
        memmove(e->adjacent_nodes + i, e->adjacent_nodes + i + 1, (e->used - i - 1) * sizeof(size_t));
    }
    e->used--;

    if (e->used < e->size - 5) {
        e->adjacent_nodes = (size_t *)realloc(e->adjacent_nodes, e->size - 5);
        assert(e->adjacent_nodes != NULL);
        e->size -= 5;
    }
}

Edges *init_edges(void) {
    Edges *e = (Edges *)malloc(sizeof(Edges));
    assert(e != NULL);
    size_t *adjacent_nodes = calloc(5, sizeof(size_t));
    assert(adjacent_nodes != NULL);
    e->adjacent_nodes = adjacent_nodes;
    e->size = 5;
    e->used = 0;

    return e;
}

void free_edges(Edges *e) {
    free(e->adjacent_nodes);
    free(e);
}

void print_edges(Edges e) {
    printf("[");
    for (size_t i = 0; i < e.used; i++) {
        printf("%lu%s", e.adjacent_nodes[i], i == e.used - 1 ? "" : ", ");
    }
    printf("]\n");
}
