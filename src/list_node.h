#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "node.h"

typedef struct ListNode {
    struct Node *node;
    struct ListNode *next_node;
} ListNode;

void add_node_at(int pos, ListNode **head, struct Node *n);

void delete_node(ListNode **head, struct Node *n);

ListNode *init_list_node(struct Node *n);

void free_list_node(ListNode *list_node);

void print_list_node(const ListNode *list_node);

int list_node_len(ListNode *ln);

#endif
