#include "coordinates.h"
#include "file_management.h"
#include "graph.h"
#include "node.h"
#include "path_finding.h"
#include "visualization.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Graph *g = init_graph();

    read_graph_from_csv("test.csv", g);
    print_graph(g);

    Node *a = find_node(g, "A");
    Node *d = find_node(g, "D");
    Path *p = find_path(g, d, a);
    print_path(p);

    display_graph_with_path(g, p);

    free_graph(g);

    return 0;
}
