#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_field(char *line, int n) {
    char *token;
    char *str = strdup(line);
    token = strtok(str, ";");
    while (token != NULL) {
        if (n == 0) {
            free(str);
            return token;
        }
        n--;
        token = strtok(NULL, ";");
    }
    free(str);
    return NULL;
}

Graph *read_graph_from_file(char *fname) {
    Graph *g = init_graph();
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t line_length;

    fp = fopen(fname, "r");
    if (fp == NULL) {
        return NULL;
    }

    while ((line_length = getline(&line, &len, fp)) != EOF) {
        char name[MAX_NAME_LENGTH];
        int x, y;

        char *field;
        field = get_field(line, 0);
        if (field != NULL && strlen(field) < MAX_NAME_LENGTH)
            strcpy(name, field);
        else
            return NULL;

        field = get_field(line, 1);
        if (field == NULL || sscanf(field, "%d", &x) != 1)
            return NULL;

        field = get_field(line, 2);
        if (field == NULL || sscanf(field, "%d", &y) != 1)
            return NULL;

        add_node_to_graph(g, *init_node(name, (Coordinate){.x = x, .y = y}));
    }

    free(line);
    return g;
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

Graph *init_graph(void) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    Node *nodes;
    nodes = (Node *)calloc(5, sizeof(Node));
    if (nodes == NULL) {
        return NULL;
    }
    g->nodes = nodes;
    g->used = 0;
    g->size = 5;
    return g;
}

void print_graph(Graph g) {
    printf("--- GRAPH ---\n");
    printf("Size: %d\n", g.size);
    printf("Number of nodes: %d\n", g.used);
    printf("Nodes:\n");

    for (int i = 0; i < g.used; i++) {
        printf("---\n");
        print_node(g.nodes[i]);
    }
}