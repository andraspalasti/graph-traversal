#include "list_node.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Adds a node to the ListNode at the specified position
 * 
 * @param pos Specifies where to add node if it is -1 it will add it to the end
 * @param head Pointer to the leading ListNode
 * @param node The node to add
 */
void add_node_at(int pos, ListNode **head, Node *n) {
    ListNode *ln = init_list_node(n);

    // if head is empty
    if (*head == NULL) {
        *head = ln;
        return;
    }

    int idx = 0;
    ListNode *prev = NULL;
    ListNode *cur = (*head);

    // walk through list until pos or end is reached
    while (cur != NULL && idx != pos) {
        idx++;
        prev = cur;
        cur = cur->next_node;
    };

    // if you want to insert to the begining
    if (prev == NULL) {
        ln->next_node = cur;
        (*head) = ln;
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

/**
 * @brief Delete the node from the ListNodes
 * 
 * @param head Pointer to the leading ListNode
 * @param n Node to delete
 */
void delete_node(ListNode **head, struct Node *n) {
    ListNode *prev_ln = NULL;
    ListNode *cur_ln = *head;

    while (cur_ln != NULL && cur_ln->node != n) {
        prev_ln = cur_ln;
        cur_ln = cur_ln->next_node;
    }
    // we could not find the specified node
    if (cur_ln == NULL)
        return;

    // if you want to delete the first node
    if (prev_ln == NULL) {
        *head = cur_ln->next_node;
        free(cur_ln);
        return;
    }

    // if you want to delete the last node
    if (cur_ln == NULL) {
        prev_ln->next_node = NULL;
        free(cur_ln);
        return;
    }

    // if you want to delet from the middle
    prev_ln->next_node = cur_ln->next_node;
    free(cur_ln);
}

/**
 * @brief Returns the number of elements that the list node contains
 * 
 * @param ln The list node to count elements in
 * @return int The number of elements
 */
int list_node_len(ListNode *ln) {
    int len = 0;
    while (ln != NULL) {
        ln = ln->next_node;
        len++;
    }
    return len;
}

/**
 * @brief Instantiates a new list_node
 * 
 * @param n Node to store
 * @return ListNode* Pointer to the created ListNode
 */
ListNode *init_list_node(struct Node *n) {
    ListNode *list_node = (ListNode *)malloc(sizeof(ListNode));
    check_malloc(list_node);
    list_node->node = n;
    list_node->next_node = NULL;
    return list_node;
}

/**
 * @brief Frees the memory allocated by the ListNode
 * ATTENTION: It does not free the nodes that are stored in it
 * 
 * @param list_node The ListNode to free
 */
void free_list_node(ListNode *list_node) {
    if (list_node == NULL)
        return;

    free_list_node(list_node->next_node);
    free(list_node);
}

/**
 * @brief Prints the ListNode in a nice formatted way to the console
 * 
 * @param list_node The ListNode to print
 */
void print_list_node(const ListNode *list_node) {
    printf("[");
    while (list_node != NULL) {
        printf("%s%s", list_node->node->name, list_node->next_node != NULL ? ", " : "");
        list_node = list_node->next_node;
    }
    printf("]\n");
}
