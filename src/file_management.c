#include "file_management.h"
#include "graph.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Reads a csv file into a graph
* The csv should look like this:
* AA;10;10;"OA,FD"
* OA;-678;-166;"AA"
* FD;31;392;"AA"
* ----
* Explanation: name;x coord;y coord;"adjacent nodes"
*/
void read_graph_from_csv(const char *fpath, Graph *g) {
    FILE *fp;
    fp = fopen(fpath, "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    read_nodes_from_csv(fp, g);
    // rewind(fp);
    // read_edges_from_csv(fp, g);

    fclose(fp);
}

/*
* Reads the nodes from a csv into a graph
*/
void read_nodes_from_csv(FILE *fp, Graph *g) {
    int line_num = 1;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != EOF) {
        char *parts[3]; // part[0] name, part[1] x coord, part[2] y coord
        int x = 0, y = 0;
        split(line, parts, 3, ";,");

        if (parts[0] == NULL) {
            printf("Badly formatted line on line number: %d", line_num);
            exit(EXIT_FAILURE);
        }

        if (parts[1] == NULL && sscanf(parts[1], "%d", &x) != 1) {
            printf("Badly formatted line on line number: %d", line_num);
            exit(EXIT_FAILURE);
        }

        if (parts[2] == NULL && sscanf(parts[2], "%d", &y) != 1) {
            printf("Badly formatted line on line number: %d", line_num);
            exit(EXIT_FAILURE);
        }

        Node *n = init_node(parts[0], (Coordinates){.x = x, .y = y});
        add_node_at(-1, g, n);

        line_num++;
    }
}
