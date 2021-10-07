#ifndef EDGES_H_
#define EDGES_H_

typedef struct Edge {
    int node_index;
} Edge;

typedef struct ArrayOfEdges {
    Edge *edges; // array
    int used;
    int size;
} ArrayOfEdges;

/*
* Adds an edge to an array of edges
*/
void add_edge(ArrayOfEdges *array, Edge edge);

/*
* Instantiates a new array of edges
*/
ArrayOfEdges init_edges(void);

/*
* Prints an edge to the console
*/
void print_edges(ArrayOfEdges array);

#endif