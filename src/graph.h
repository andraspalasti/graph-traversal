#include "coordinate.h"
#include "edges.h"

typedef struct Node {
    int id;
    char name[10];
    Coordinate coord;
    Edges neighbors;
} Node;

typedef struct Graph {
    Node *nodes; // array of nodes
    int used;
    int size;
} Graph;

Graph init_graph(void);

void add_node_to_graph(Graph *g, Node n);

void print_node(Node n);

void print_graph(Graph g);