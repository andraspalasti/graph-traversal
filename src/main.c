#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Graph *g = read_graph_from_file("nodes.csv");
    if (g == NULL) {
        printf("Error: There was a problem with the file\n");
        // This could mean:
        // - could not open file
        // - wrong separator csv should be separated with ';'
        // - in a line it could not find name or x or y coords
        exit(EXIT_FAILURE);
    }

    print_graph(*g);

    return 0;
}