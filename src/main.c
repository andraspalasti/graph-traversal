#include "node.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Node *n = init_node("A", (Coordinates){.x = 10, .y = 10});
    Node *n1 = init_node("B", (Coordinates){.x = 20, .y = 10});
    Node *n2 = init_node("C", (Coordinates){.x = 30, .y = 10});

    print_node(*n);
    add_neighbour_at(0, n, n1);
    add_neighbour_at(0, n, n2);
    print_node(*n);

    free_node(n);
    free_node(n1);
    free_node(n2);

    return 0;
}
