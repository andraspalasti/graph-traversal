typedef struct Edge {
    int node_index;
} Edge;

typedef struct Edges {
    Edge *edges; // array of edges
    int used;
    int size;
} Edges;