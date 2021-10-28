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

    print_graph(g);

    read_graph_from_csv("test.csv", g);
    // draw_graph("graph.svg", g);
    print_graph(g);

    free_graph(g);

    return 0;
}
