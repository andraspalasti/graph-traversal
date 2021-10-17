#include "coordinates.h"
#include "graph.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Graph *g = init_graph();

    Node *n = init_node("A", (Coordinates){.x = 10, .y = 10});
    Node *n1 = init_node("B", (Coordinates){.x = 20, .y = 10});
    Node *n2 = init_node("C", (Coordinates){.x = 30, .y = 10});

    print_graph(g);
    add_neighbour_at(0, n, n1);
    add_neighbour_at(0, n, n2);
    add_node_at(0, g, n);
    add_node_at(0, g, n1);
    add_node_at(0, g, n2);
    print_graph(g);

    free_graph(g);

    return 0;
}
