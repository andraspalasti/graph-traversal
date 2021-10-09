#include "edges.h"
#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
