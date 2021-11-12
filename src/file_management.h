#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include "graph.h"
#include <stdio.h>

void read_graph_from_csv(const char *fpath, Graph *g);

void read_nodes_from_csv(FILE *fp, Graph *g);

void read_edges_from_csv(FILE *fp, Graph *g);

void save_graph_to_csv(const char *fpath, const Graph *g);

#endif
