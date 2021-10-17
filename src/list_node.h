#ifndef list_node_H_
#define list_node_H_

#include "node.h"

typedef struct ListNode {
    struct Node *node;
    struct ListNode *next_node;
} ListNode;

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
void print_list_node(ListNode *list_node);

#endif
