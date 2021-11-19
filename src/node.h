#ifndef NODE_H
#define NODE_H

#include "coordinates.h"
#include "list_node.h"
#include <stdbool.h>

#define NODE_NAME_LEN 20

typedef struct Node {
    char name[NODE_NAME_LEN + 1];
    Coordinates coords;
    struct ListNode *neighbours;
} Node;

void add_neighbour_at(int pos, Node *n, Node *adjacent_node);

void remove_neighbour(Node *n, Node *neighbour);

bool is_connected(const Node *a, const Node *b);

Node *init_node(const char *name, Coordinates coords);

void free_node(Node *n);

void print_node(const Node *n);

#endif
