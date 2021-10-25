#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "node.h"

typedef struct ListNode {
    struct Node *node;
    struct ListNode *next_node;
} ListNode;

/*
* Adds a list node to the head at the specified position
*/
void add_list_node_at(int pos, ListNode **head, ListNode *ln);

/*
* Delete the node from the list node
*/
void delete_list_node(ListNode **head, struct Node *n);

/*
* Instantiates a new list_node
*/
ListNode *init_list_node(struct Node *n);

/*
* Frees the memory allocated by the list_node
*/
void free_list_node(ListNode *list_node);

/*
* Prints a list_node to the console
*/
void print_list_node(const ListNode *list_node);

#endif
