#include "list_node.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Instantiates a new list_node
*/
ListNode *init_list_node(Node *n) {
    ListNode *list_node = (ListNode *)malloc(sizeof(ListNode));
    assert(list_node != NULL);
    list_node->node = n;
    list_node->next_node = NULL;
    return list_node;
}

/*
* Frees the memory allocated by the list_node
* !!!Attention this does not free the node field
*/
void free_list_node(ListNode *list_node) {
    if (list_node == NULL)
        return;

    free_list_node(list_node->next_node);
    free(list_node);
}

/*
* Prints the list_nodes to the console
*/
void print_list_node(ListNode *list_node) {
    printf("[");
    while (list_node != NULL) {
        printf("%s%s", list_node->node->name, list_node->next_node != NULL ? ", " : "");
        list_node = list_node->next_node;
    }
    printf("]\n");
}
