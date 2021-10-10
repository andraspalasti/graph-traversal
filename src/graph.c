#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// char *get_field(char *line, int n) {
// char *token;
// char *str = strdup(line);
// if (str == NULL)
// return NULL;

// token = strtok(str, ";");
// while (token != NULL) {
// if (n == 0) {
// free(str);
// return token;
// }
// n--;
// token = strtok(NULL, ";");
// }
// free(str);
// return NULL;
// }

// Graph *read_graph_from_file(char *fpath) {
// FILE *fp;

// fp = fopen(fpath, "r");
// if (fp == NULL) {
// perror("fopen");
// return NULL;
// }

// Graph *g = init_graph();
// char *line = NULL;
// size_t len = 0;
// int line_num = 1;

// while (getline(&line, &len, fp) != EOF) {
// char *name;
// char *field;
// int x, y;

// field = get_field(line, 0);
// if (field != NULL) {
// name = strdup(field);
// if (name == NULL) {
// return NULL;
// }
// } else {
// printf("You did not provide a name in your file on line %d\n", line_num);
// return NULL;
// }

// field = get_field(line, 1);
// if (field == NULL || sscanf(field, "%d", &x) != 1) {
// printf("You did not provide an x Coordinates in your file on line %d\n", line_num);
// return NULL;
// }

// field = get_field(line, 2);
// if (field == NULL || sscanf(field, "%d", &y) != 1) {
// printf("You did not provide a y Coordinates in your file on line %d\n", line_num);
// return NULL;
// }

// // Node *n = init_node(name, (Coordinates){.x = x, .y = y});
// // if (n == NULL) {
// // return NULL;
// // }

// // add_node_to_graph(g, *n);
// line_num++;
// }

// fclose(fp);
// return g;
// }

// void add_node_to_graph(Graph *g, Node n) {
// if (g->used == g->size) {
// g->size += 5;
// Node *nodes = realloc(g->nodes, g->size * sizeof(Node));
// if (nodes == NULL) {
// // dont know what to do if we get a NULL pointer
// }
// g->nodes = nodes;
// }
// g->nodes[g->used++] = n;
// }

// Graph *init_graph(void) {
// Graph *g = (Graph *)malloc(sizeof(Graph));
// if (g == NULL)
// return NULL;

// Node *nodes = (Node *)calloc(5, sizeof(Node));
// if (nodes == NULL) {
// free(g);
// return NULL;
// }
// g->nodes = nodes;
// g->used = 0;
// g->size = 5;
// return g;
// }
