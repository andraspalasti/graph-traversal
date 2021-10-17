// #include "file_management.h"
// #include "graph.h"
// #include <assert.h>
// #include <stdio.h>
// #include <string.h>

// /*
// * Reads a csv file into a graph
// * The csv should look like this:
// * AA;10;10;"OA,FD"
// * OA;-678;-166;"AA"
// * FD;31;392;"AA"
// * ----
// * Explanation: name;x coord;y coord; adjacent nodes
// */
// void read_graph_from_csv(const char *fpath, Graph *g) {
// // char *str = malloc(8 * sizeof(char));
// // printf("%s", str);
// FILE *fp;
// fp = fopen(fpath, "r");
// if (fp == NULL) {
// perror("fopen");
// exit(EXIT_FAILURE);
// }
// read_nodes_from_csv(fp, g);
// rewind(fp);
// read_edges_from_csv(fp, g);

// fclose(fp);
// }

// void read_nodes_from_csv(FILE *fp, Graph *g) {
// char *line = NULL;
// size_t len = 0;
// int line_num = 1;

// while (getline(&line, &len, fp) != EOF) {
// char *name;
// char *field;
// int x, y;

// field = get_field(line, 1);
// if (field == NULL) {
// printf("You did not provide a name in your file on line %d\n", line_num);
// exit(EXIT_FAILURE);
// }
// name = strdup(field);
// assert(name != NULL);

// field = get_field(line, 2);
// if (field == NULL || sscanf(field, "%d", &x) != 1 || x < -500 || 500 < x) {
// printf("You did not provide a valid x coordinate in your file on line %d\n", line_num);
// printf("A valid x coordinate is a whole number that is between -500 and 500\n");
// exit(EXIT_FAILURE);
// }

// field = get_field(line, 3);
// if (field == NULL || sscanf(field, "%d", &y) != 1 || y < -500 || 500 < y) {
// printf("You did not provide a valid y coordinate in your file on line %d\n", line_num);
// printf("A valid y coordinate is a whole number that is between -500 and 500\n");
// exit(EXIT_FAILURE);
// }

// Node *n = init_node(name, (Coordinates){.x = x, .y = y});
// free(name);
// assert(n != NULL);
// add_node(g, n);

// line_num++;
// }
// }

// void read_edges_from_csv(FILE *fp, Graph *g) {
// char *line = NULL;
// size_t len = 0;
// int line_num = 1;

// while (getline(&line, &len, fp) != EOF) {
// char *name;
// char *adjacent_nodes;

// name = get_field(line, 1);
// if (name == NULL) {
// printf("You did not provide a node name in your file on line %d\n", line_num);
// exit(EXIT_FAILURE);
// }

// Node *node = search_for_node(*g, name);
// if (node != NULL) {
// adjacent_nodes = get_field(line, 4);
// remove_chr_from_str(adjacent_nodes, '\n');
// remove_chr_from_str(adjacent_nodes, '\"');

// char *adjacent_node_name = strtok(adjacent_nodes, ",");
// while (adjacent_node_name != NULL) {
// long int adjacent_node_idx = search_for_node_idx(*g, adjacent_node_name);
// if (adjacent_node_idx != -1) {
// add_node_idx(node->neighbors, (size_t)adjacent_node_idx);
// }
// adjacent_node_name = strtok(NULL, ",");
// }
// }

// line_num++;
// }
// }

// /*
// * Gets the nth field from line separated by ';'
// * Example:
// * get_field("AA;10;15", 2) returns: "10"
// */
// char *get_field(char *line, int n) {
// assert(n > 0);
// char *token;
// char *str = strdup(line);
// if (str == NULL)
// return NULL;

// token = strtok(str, ";");
// while (token != NULL) {
// if (n == 1) {
// // free(str);
// return token;
// }
// n--;
// token = strtok(NULL, ";");
// }
// // free(str);
// return NULL;
// }

// /*
// * Removes all occurrences of a char from a string
// */
// void remove_chr_from_str(char *str, char chr_to_delete) {
// char *c;
// while ((c = strchr(str, chr_to_delete)) != NULL) {
// memmove(c, c + 1, strlen(c));
// }
// }
