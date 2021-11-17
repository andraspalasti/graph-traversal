#include "path_finding.h"
#include "../include/debugmalloc.h"
#include "hash_tables/hash_table_n.h"
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

    // with this table we can traverse back to find the complete path
    HashTableN *prev = init_hash_table_n(g->used);

    // fill with default values
    for (int i = 0; i < g->used; i++) {
        if (g->nodes[i] == src)
            dist[i] = 0;
        else
            dist[i] = INFINITY;
        prev->set(prev, g->nodes[i]->name, NULL);
        enqueue(q, g->nodes[i]);
    }

    while (q->head != NULL) {
        Node *n = min_dist_node(q, dist);
        dequeue(q, n);

        if (prev->get(prev, n->name) != NULL && n == target) {
            // we found the end of the path and we need to traverse it back
            Path *p = NULL;
            Node *cur = n;
            while (cur != NULL) {
                add_node_at(0, &p, cur);
                cur = prev->get(prev, cur->name);
            }
            prev->free_table(prev);
            free(dist);
            free_queue(q);
            return p;
        }

        ListNode *neighbour = n->neighbours;
        while (neighbour != NULL) {
            double alt_route = dist[n->idx] + distance(n->coords, neighbour->node->coords);
            // check if the this route is shorter than the known
            if (alt_route < dist[neighbour->node->idx]) {
                dist[neighbour->node->idx] = alt_route;
                prev->set(prev, neighbour->node->name, n);
            }
            neighbour = neighbour->next_node;
        }
    }

    // there is no path
    prev->free_table(prev);
    free(dist);
    free_queue(q);
    return NULL;
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
