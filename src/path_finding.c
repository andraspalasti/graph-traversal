#include "path_finding.h"
#include "queue.h"
#include "util.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: we should implement a hash table because this is wack

/**
 * @brief It finds the possible shortest path between src and target
 * 
 * @param g
 * @param src Start node
 * @param target Destination node
 * @return Path* If there is no path between the nodes than it returns a NULL pointer
 */
Path *find_path(Graph *g, Node *src, Node *target) {
    Queue *q = init_queue();

    // in this array we will store the shortest distance from the src node
    // to the node with the corresponding index
    double *dist = (double *)malloc(g->used * sizeof(double));
    check_malloc(dist);

    // in this array we will store the shortest route that is
    // needed to take to the src node
    Node **prev = (Node **)malloc(g->used * sizeof(Node *));
    check_malloc(prev);

    // fill with default values
    for (int i = 0; i < g->used; i++) {
        if (g->nodes[i] == src)
            dist[i] = 0;
        else
            dist[i] = INFINITY;
        prev[i] = NULL;
        enqueue(q, g->nodes[i]);
    }

    Path *p = NULL;
    while (q->head != NULL) {
        Node *n = min_dist_node(q, dist);
        dequeue(q, n);

        if (prev[n->idx] != NULL && n == target) {
            Node *cur = n;
            while (cur != NULL) {
                add_node_at(0, &p, cur);
                cur = prev[cur->idx];
            }
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

/**
 * @brief Frees the memory allocated by the Path
 * 
 * @param p The Path to free
 */
void free_path(Path *p) {
    free_list_node(p);
}

/**
 * @brief Prints the path to the console in a nicely formatted way
 * 
 * @param p The Path to free
 */
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

// TODO: This would be better if we would do a pop rather than this
/**
 * @brief Returns a pointer to the node from the Queue that has the
 * least amount of distance in the dist array
 * 
 * @param q 
 * @param dist An array that stores the distance for each node
 * @return Node* 
 */
Node *min_dist_node(Queue *q, const double *dist) {
    assert(q != NULL);
    assert(q->head != NULL);

    Node *min = q->head->node;
    ListNode *cur = q->head;
    while (cur != NULL) {
        if (dist[cur->node->idx] < dist[min->idx]) {
            min = cur->node;
        }
        cur = cur->next_node;
    }

    return min;
}
