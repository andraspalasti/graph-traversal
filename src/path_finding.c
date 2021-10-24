#include "path_finding.h"
#include "util.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Path *find_path(Graph *g, Node *src, Node *target) {
    Queue *q = NULL;
    double *dist = (double *)malloc(g->used * sizeof(double));
    check_malloc(dist);
    Node **prev = (Node **)malloc(g->used * sizeof(Node *));
    if (prev == NULL) {
        free(dist);
        print_error("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // fill with default values
    for (int i = 0; i < g->used; i++) {
        if (g->nodes[i] == src)
            dist[i] = 0;
        else
            dist[i] = INFINITY;
        prev[i] = NULL;
        enqueue(0, &q, init_queue(g->nodes[i]));
    }

    Path *p = NULL;
    while (q != NULL) {
        Node *n = min_dist_node(q, dist);
        remove_from_queue(&q, n);

        if (prev[n->idx] != NULL && n == target) {
            load_path(&p, prev, n);
            break;
        }

        ListNode *neighbour = n->neighbours;
        while (neighbour != NULL) {
            double alt_route = dist[n->idx] + distance(n->coords, neighbour->node->coords);
            if (alt_route < dist[neighbour->node->idx]) {
                dist[neighbour->node->idx] = alt_route;
                prev[neighbour->node->idx] = n;
            }
            neighbour = neighbour->next_node;
        }
    }

    free(prev);
    free(dist);
    free_queue(q);
    return p;
}

void load_path(Path **p, Node **prev, Node *end) {
    Node *cur = end;
    while (cur != NULL) {
        ListNode *ln = init_list_node(cur);
        add_list_node_at(0, p, ln);
        cur = prev[cur->idx];
    }
}

void free_path(Path *p) {
    free_list_node(p);
}

void print_path(Path *p) {
    Path *cur = p;
    while (cur != NULL) {
        printf("%s", cur->node->name);
        if (cur->next_node != NULL)
            printf(" -> ");

        cur = cur->next_node;
    }
    printf("\n");
}

Node *min_dist_node(Queue *q, const double *dist) {
    if (q == NULL)
        return NULL;

    Node *min = q->node;
    Queue *cur = q;
    while (cur != NULL) {
        if (dist[cur->node->idx] < dist[min->idx]) {
            min = cur->node;
        }
        cur = cur->next_node;
    }

    return min;
}

void enqueue(int pos, Queue **head, Queue *q) {
    add_list_node_at(pos, head, q);
}

void remove_from_queue(Queue **q, Node *n) {
    delete_list_node(q, n);
}

Queue *init_queue(Node *n) {
    return init_list_node(n);
}

void free_queue(Queue *q) {
    free_list_node(q);
}
