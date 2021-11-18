#include "path_finding.h"
#include "../include/debugmalloc.h"
#include "hash_table.h"
#include "queue.h"
#include "util.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static Node *nearest_node(const Queue *q, const HashTable *dist);

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

    // in this table we store the shortest distance that is needed to take to a node
    HashTable *dist = init_ht(g->used);
    double *distances = malloc(g->used * sizeof(double));
    check_malloc(distances);

    // with this table we can traverse back to find the complete path
    HashTable *prev = init_ht(g->used);

    // fill with default values
    for (int i = 0; i < g->used; i++) {
        if (g->nodes[i] == src) {
            distances[i] = 0;
            set_value_ptr(dist, g->nodes[i]->name, &(distances[i]));
        } else {
            distances[i] = INFINITY;
            set_value_ptr(dist, g->nodes[i]->name, &(distances[i]));
        }
        set_value_ptr(prev, g->nodes[i]->name, NULL);
        enqueue(q, g->nodes[i]);
    }

    while (q->head != NULL) {
        Node *n = nearest_node(q, dist);
        dequeue(q, n);
        Node *prev_nearest = ht_get_value(prev, n->name);
        if (prev_nearest != NULL && n == target) {
            // we found the end of the path and we need to traverse it back
            Path *p = NULL;
            Node *cur = n;
            while (cur != NULL) {
                add_node_at(0, &p, cur);
                cur = ht_get_value(prev, cur->name);
            }
            ht_free(prev);
            ht_free(dist);
            free(distances);
            free_queue(q);
            return p;
        }

        ListNode *neighbour = n->neighbours;
        while (neighbour != NULL) {
            double *dist_to_cur = ht_get_value(dist, n->name); // the distance to the current node
            assert(dist_to_cur != NULL);                       // can not be null because we already set a default value

            // the distance of the current route that we are traversing
            double alt_route = *dist_to_cur + distance(n->coords, neighbour->node->coords);

            // if we already touched this node it will be the distance of that route
            // else it will be INFINITY
            double *route_dist = ht_get_value(dist, neighbour->node->name);
            assert(route_dist != NULL); // can not be null because we already set a default value

            // check if the this route is shorter than the known
            if (alt_route < *route_dist) {
                *route_dist = alt_route;
                set_value_ptr(prev, neighbour->node->name, n); // now it points to another node
            }
            neighbour = neighbour->next_node;
        }
    }

    // there is no path
    ht_free(prev);
    ht_free(dist);
    free(distances);
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

/**
 * @brief Returns a pointer to the node from the Queue that has the
 * least amount of distance in the HashTable
 * 
 * @param q The queue to search in
 * @param dist The HashTable that stores how far is each node
 * @return Node* pointer to the nearest node 
 * could be a NULL pointer if no node is in the HashTable 
 */
static Node *nearest_node(const Queue *q, const HashTable *dist) {
    if (q == NULL || q->head == NULL)
        return NULL;

    ListNode *cur = q->head;

    Node *nearest_node = cur->node;
    double *min_dist = ht_get_value(dist, nearest_node->name);
    while (cur != NULL) {
        double *cur_dist = ht_get_value(dist, cur->node->name);
        if (cur_dist != NULL) {
            if (min_dist == NULL) {
                nearest_node = cur->node;
                min_dist = cur_dist;
            } else if (*cur_dist < *min_dist) {
                nearest_node = cur->node;
                min_dist = cur_dist;
            }
        }
        cur = cur->next_node;
    }

    return min_dist == NULL ? NULL : nearest_node;
}
