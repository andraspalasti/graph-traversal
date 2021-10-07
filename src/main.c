#include "graph.h"
#include <stdio.h>

int main(void) {
    Graph g = init_graph();

    char name = 'A';

    for (int i = 0; i < 32; i++) {
        Node n = {.id = i + 1,
                  .name = name + i,
                  .coord = {.x = i, .y = i}};
        add_node_to_graph(&g, n);
    }

    print_graph(g);

    return 0;
}