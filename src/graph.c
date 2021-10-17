#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Adds a node to the graph at the specified position
* @param pos starts at 0, you can insert to the end with pos = -1
*/
void add_node_at(int pos, Graph *g, Node *n) {
    ListNode *ln = init_list_node(n);
    assert(ln != NULL);

    // if graph is empty
    if (g->nodes == NULL) {
        g->nodes = ln;
        return;
    }

    int idx = 0;
    ListNode *prev = NULL;
    ListNode *cur = g->nodes;

    // walk through list until pos or end is reached
    while (cur != NULL && idx != pos) {
        idx++;
        prev = cur;
        cur = cur->next_node;
    };

    // if you want to insert to the begining
    if (prev == NULL) {
        ln->next_node = cur;
        g->nodes = ln;
        return;
    }

    // if you want to insert to the end
    if (cur == NULL) {
        prev->next_node = ln;
        return;
    }

    // if you want to insert to the middle
    prev->next_node = ln;
    ln->next_node = cur;
}

/*
* Instantiates a new graph
*/
Graph *init_graph(void) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    assert(g != NULL);

    g->nodes = NULL;

    return g;
}

void free_graph_node(ListNode *list_node) {
    if (list_node == NULL)
        return;

    free_graph_node(list_node->next_node);
    free_node(list_node->node);
    free(list_node);
}

/*
* Frees the memory allocated by the graph
*/
void free_graph(Graph *g) {
    free_graph_node(g->nodes);
    free(g);
}

/*
* Prints a graph to the console
*/
void print_graph(Graph *g) {
    if (g->nodes == NULL) {
        printf("There are no nodes in your graph\n");
        return;
    }

    printf("--- GRAPH ---\n");
    ListNode *cur = g->nodes;
    while (cur != NULL) {
        print_node(*(cur->node));
        cur = cur->next_node;
    }
}
