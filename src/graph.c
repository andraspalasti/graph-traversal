#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Instantiates a new graph
*/
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
Graph *free_graph(void);

/*
* Prints a graph to the console
*/
void print_graph(Graph g);

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

// void print_graph(Graph g) {
// printf("--- GRAPH ---\n");
// printf("Size: %d\n", g.size);
// printf("Number of nodes: %d\n", g.used);
// printf("Nodes:\n");

// for (int i = 0; i < g.used; i++) {
// printf("---\n");
// print_node(g.nodes[i]);
// }
// }
