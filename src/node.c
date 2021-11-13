#include "node.h"
#include "list_node.h"
#include "util.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Adds a neighbour to the node at the specified position
 * 
 * @param pos Specifies where to add neighbour if it is -1 it will add it to the end
 * @param n Node to add neighbour to
 * @param adjacent_node Neighbour to add
 */
void add_neighbour_at(int pos, Node *n, Node *adjacent_node) {
    add_node_at(pos, &(n->neighbours), adjacent_node);
}

/**
 * @brief Adds a neighbour to the node at the specified position
 * 
 * @param n Node to remove neighbour from
 * @param neighbour the neighbour node to remove
 */
void remove_neighbour(Node *n, Node *neighbour) {
    delete_node(&(n->neighbours), neighbour);
}

/**
 * @brief Checks if a Node has a connection to b Node
 * 
 * @param a 
 * @param b 
 * @return bool 
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

/**
 * @brief Instantiates a new node
 * 
 * @param name The node name to instantiate with
 * @param coords 
 * @return Node* 
 */
Node *init_node(const char *name, Coordinates coords) {
    assert(strlen(name) <= NODE_NAME_LEN);
    Node *n = (Node *)malloc(sizeof(Node));
    check_malloc(n);

    strcpy(n->name, name);
    n->idx = -1;
    n->coords = coords;
    n->neighbours = NULL;
    return n;
}

/**
 * @brief Frees the memory allocated by the node
 * 
 * @param n 
 */
void free_node(Node *n) {
    free_list_node(n->neighbours);
    free(n);
}

/**
 * @brief Prints the node to the console in a nice formatted way
 * 
 * @param n Node to print
 */
void print_node(const Node *n) {
    if (n->idx != -1)
        printf("idx: %d, ", n->idx);
    printf("name: %s, coords: ", n->name);
    print_coords(n->coords);

    printf("Neighbours: ");
    print_list_node(n->neighbours);
}
