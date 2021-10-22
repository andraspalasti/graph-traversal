#ifndef FILE_MANAGEMENT_H_
#define FILE_MANAGEMENT_H_

#include "graph.h"
#include <stdio.h>

/*
* Reads a csv file into a graph
* The csv should look like this:
* AA;10;10;"OA,FD"
* OA;-678;-166;"AA"
* FD;31;392;"AA"
* ----
* Explanation: name;x coord;y coord;"adjacent nodes"
*/
void read_graph_from_csv(const char *fpath, Graph *g);

/*
* Reads the nodes from a csv into a graph
*/
void read_nodes_from_csv(FILE *fp, Graph *g);

#endif
