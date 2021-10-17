// Graph *init_graph(void) {
// Graph *g = (Graph *)malloc(sizeof(Graph));
// assert(g != NULL);

// Node **nodes = (Node **)calloc(5, sizeof(Node *));
// assert(nodes != NULL);

// g->nodes = nodes;
// g->used = 0;
// g->size = 5;

// return g;
// }

// /*
// * Frees the memory allocated by the graph
// */
// void free_graph(Graph *g) {
// for (size_t i = 0; i < g->used; i++) {
// free_node(g->nodes[i]);
// }
// free(g->nodes);
// free(g);
// }

// /*
// * Prints a graph to the console
// */
// void print_graph(Graph g) {
// printf("--- GRAPH ---\n");
// printf("Size: %zu\n", g.size);
// printf("Number of nodes: %zu\n", g.used);
// printf("Nodes:\n");

// for (size_t i = 0; i < g.used; i++) {
// printf("---\n");
// print_node(*(g.nodes[i]));
// }
// }
