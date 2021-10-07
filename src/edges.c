#include "edges.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void add_edge(ArrayOfEdges *array, Edge edge) {
    // if we dont have enough memory for next edge we need to reallocate it
    if (array->used == array->size) {
        array->size += 5;
        Edge *edges;
        edges = (Edge *)realloc(array->edges, array->size * sizeof(Edge));
        if (edges == NULL) {
            // dont know what to do if we get a NULL pointer
        }
        array->edges = edges;
    }
    array->edges[array->used++] = edge;
}

ArrayOfEdges init_edges(void) {
    Edge *edges;
    edges = (Edge *)calloc(5, sizeof(Edge));
    if (edges == NULL) {
        // dont know what to do if we get a NULL pointer
    }
    return (ArrayOfEdges){.edges = edges, .used = 0, .size = 5};
}

void print_edges(ArrayOfEdges array) {
    printf("[");
    for (int i = 0; i < array.used; i++) {
        printf("%d%s", array.edges[i].node_index, i == array.used - 1 ? "" : ", ");
    }
    printf("]\n");
}
