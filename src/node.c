#include "node.h"
#include "list_node.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Adds a neighbour to the node at the specified position
* @param pos starts at 0, you can insert to the end with pos = -1
*/
void add_neighbour_at(int pos, Node *n, Node *adjacent_node) {
    ListNode *neighbour = init_list_node(adjacent_node);

    // if neighbour list is empty
    if (n->neighbours == NULL) {
        n->neighbours = neighbour;
        return;
    }

    int idx = 0;
    ListNode *prev = NULL;
    ListNode *cur = n->neighbours;

    // walk through list until pos or end is reached
    while (cur != NULL && idx != pos) {
        idx++;
        prev = cur;
        cur = cur->next_node;
    };

    // if you want to insert to the begining
    if (prev == NULL) {
        neighbour->next_node = cur;
        n->neighbours = neighbour;
        return;
    }

    // if you want to insert to the end
    if (cur == NULL) {
        prev->next_node = neighbour;
        return;
    }

    // if you want to insert to the middle
    prev->next_node = neighbour;
    neighbour->next_node = cur;
}

/*
* Instantiates a new node
*/
Node *init_node(const char *name, Coordinates coords) {
    Node *n = (Node *)malloc(sizeof(Node));
    check_malloc(n);

    n->name = strdup(name);
    if (n->name == NULL) {
        free(n);
        printf("Failed to allocate memory!\n");
        exit(EXIT_FAILURE);
    }

    n->coords = coords;
    n->neighbours = NULL;

    return n;
}

/*
* Frees the memory allocated by the node
*/
void free_node(Node *n) {
    free_list_node(n->neighbours);
    free(n->name);
    free(n);
}

/*
* Prints a node to the console
*/
void print_node(const Node *n) {
    printf("name: %s, coords: ", n->name);
    print_coords(n->coords);

    printf("Neighbours: ");
    print_list_node(n->neighbours);
}
