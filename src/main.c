#include "coordinates.h"
#include "file_management.h"
#include "graph.h"
#include "node.h"
#include "path_finding.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Graph *g = init_graph();

    print_graph(g);

    read_graph_from_csv("test.csv", g);

    print_graph(g);
    Node *src = find_node(g, "AA");
    Node *target = find_node(g, "UL");
    if (src != NULL && target != NULL) {
        Path *p = find_path(g, src, target);
        if (p == NULL)
            printf("No path was found\n");
        else
            print_path(p);
        free_path(p);
    }

    free_graph(g);

    return 0;
}
