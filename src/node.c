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
    add_list_node_at(pos, &(n->neighbours), neighbour);
}

/*
* Removes the neighbour from the specified node
*/
void remove_neighbour(Node *n, Node *neighbour) {
    delete_list_node(&(n->neighbours), neighbour);
}

/*
* Checks if a is connected to b
*/
bool is_connected(const Node *a, const Node *b) {
    ListNode *neighbour = a->neighbours;
    while (neighbour != NULL) {
        if (neighbour->node == b) {
            return true;
        }
        neighbour = neighbour->next_node;
    }
    return false;
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
        print_error("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    n->idx = -1;
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
    if (n->idx != -1)
        printf("idx: %d, ", n->idx);
    printf("name: %s, coords: ", n->name);
    print_coords(n->coords);

    printf("Neighbours: ");
    print_list_node(n->neighbours);
}
