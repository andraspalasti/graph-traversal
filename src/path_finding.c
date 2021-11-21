#include "path_finding.h"
#include "../include/debugmalloc.h"
#include "hash_tables/hash_table.h"
#include "hash_tables/hash_table_d.h"
#include "queue.h"
#include "util.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static Node *nearest_node(const Queue *q, const HashTableD *dist);

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
    HashTableD *dist = init_ht_d(g->used);

    // with this table we can traverse back to find the complete path
    HashTable *prev = init_ht(g->used);

    // fill with default values
    for (int i = 0; i < g->used; i++) {
        dist->set(dist, g->nodes[i]->name, g->nodes[i] == src ? 0 : INFINITY);
        prev->set(prev, g->nodes[i]->name, NULL);
        enqueue(q, g->nodes[i]);
    }

    while (q->head != NULL) {
        Node *n = nearest_node(q, dist);
        dequeue(q, n);

        // if we reached target it means that we found the shortest path
        if (n == target)
            break;

        ListNode *neighbour = n->neighbours;
        while (neighbour != NULL) {
            double *dist_to_cur = dist->get(dist, n->name); // the distance to the current node
            assert(dist_to_cur != NULL);                    // can not be null because we already set a default value

            // the distance of the current route that we are traversing
            double alt_route = *dist_to_cur + distance(n->coords, neighbour->node->coords);

            // if we already touched this node it will be the distance of that route
            // else it will be INFINITY
            double *route_dist = dist->get(dist, neighbour->node->name);
            assert(route_dist != NULL); // can not be null because we already set a default value

            // check if the this route is shorter than the known
            if (alt_route < *route_dist) {
                *route_dist = alt_route;
                prev->set(prev, neighbour->node->name, n); // now it points to another node that is closer
            }
            neighbour = neighbour->next_node;
        }
    }
    Path *p = NULL;

    // if there is a node in prev[target] it means we found the shortest path
    // so we need to traverse it back
    Node **prev_node = (Node **)prev->get(prev, target->name);
    assert(prev_node != NULL); // it should not be null because we set a default value for all nodes
    if (*prev_node != NULL) {
        add_node_at(0, &p, target);
        while (*prev_node != NULL) {
            // if we always push to the front it will be in the right order
            add_node_at(0, &p, *prev_node);
            prev_node = (Node **)prev->get(prev, (*prev_node)->name);
            assert(prev_node != NULL); // it should not be null because we set a default value for all nodes
        }
    }

    prev->ht_free(prev);
    dist->ht_free(dist);
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

/**
 * @brief Returns a pointer to the node from the Queue that has the
 * least amount of distance in the HashTable
 * 
 * @param q The queue to search in
 * @param dist The HashTable that stores how far is each node
 * @return Node* pointer to the nearest node 
 * could be a NULL pointer if no node is in the HashTable 
 */
static Node *nearest_node(const Queue *q, const HashTableD *dist) {
    if (q == NULL || q->head == NULL)
        return NULL;

    ListNode *cur = q->head;

    Node *nearest_node = cur->node;
    double *min_dist = dist->get(dist, nearest_node->name);
    while (cur != NULL) {
        double *cur_dist = dist->get(dist, cur->node->name);
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
