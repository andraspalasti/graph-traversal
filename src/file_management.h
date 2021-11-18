#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include "graph.h"
#include <stdio.h>

void read_graph_from_csv(const char *fpath, Graph *g);

void save_graph_to_csv(const char *fpath, const Graph *g);

#endif
