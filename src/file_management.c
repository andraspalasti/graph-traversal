#include "file_management.h"
#include "../include/debugmalloc.h"
#include "graph.h"
#include "util.h"
#include "visualization.h"
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void read_nodes_from_csv(FILE *fp, Graph *g);

static void read_edges_from_csv(FILE *fp, Graph *g);

/**
 * @brief Reads a csv file into a graph
 * 
 * @param fpath path of csv file
 * @param g The graph to read into
 */
void read_graph_from_csv(const char *fpath, Graph *g) {
    assert(strstr(fpath, ".csv") != NULL);
    FILE *fp;
    fp = fopen(fpath, "rt");
    if (fp == NULL) {
        print_error("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    read_nodes_from_csv(fp, g);
    rewind(fp);
    read_edges_from_csv(fp, g);

    fclose(fp);
}

/**
 * @brief Reads the nodes from file
 * 
 * @param fpath path of csv file
 * @param g The graph to read into
 */
static void read_nodes_from_csv(FILE *fp, Graph *g) {
    int line_num = 1;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != EOF) {
        char *parts[3]; // part[0] name, part[1] x coord, part[2] y coord
        double x = 0, y = 0;
        split(line, parts, 3, ";");

        if (parts[0] == NULL) {
            print_error("Line is missing name (line number: %d)", line_num);
            exit(EXIT_FAILURE);
        } else if (strlen(parts[0]) > NODE_NAME_LEN) {
            print_error("The name of the node is too long at max it can be %d chars (line number: %d)", NODE_NAME_LEN, line_num);
            exit(EXIT_FAILURE);
        }

        if (parts[1] == NULL || sscanf(parts[1], "%lf", &x) != 1) {
            print_error("Line is missing x coordinate (line number: %d)", line_num);
            exit(EXIT_FAILURE);
        }
        if (fabs(x) > MAX_X_COORD) {
            print_error("X coordinate should be between %d and %d (line number: %d)", MAX_X_COORD, -MAX_X_COORD, line_num);
            exit(EXIT_FAILURE);
        }

        if (parts[2] == NULL || sscanf(parts[2], "%lf", &y) != 1) {
            print_error("Line is missing y coordinate (line number: %d)", line_num);
            exit(EXIT_FAILURE);
        }
        if (fabs(y) > MAX_Y_COORD) {
            print_error("Y coordinate should be between %d and %d (line number: %d)", MAX_Y_COORD, -MAX_Y_COORD, line_num);
            exit(EXIT_FAILURE);
        }

        Node *n = init_node(parts[0], (Coordinates){.x = x, .y = y});
        add_node_to_graph(g, n);

        line_num++;
    }
}

/**
 * @brief Reads the edges from file
 * 
 * @param fp 
 * @param g 
 */
static void read_edges_from_csv(FILE *fp, Graph *g) {
    int line_num = 1;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != EOF) {
        char *parts[4]; // part[0] name, part[1] x coord, part[2] y coord, part[3] adjacent nodes
        split(line, parts, 4, ";");

        Node *n = find_node(g, parts[0]);
        if (n != NULL && parts[3] != NULL) {
            remove_chars(parts[3], '"');
            trim(parts[3]);
            char *adjacent_node_name = strtok(parts[3], ",");

            while (adjacent_node_name != NULL) {
                Node *adjacent_node = find_node(g, adjacent_node_name);
                if (adjacent_node != NULL) {
                    add_neighbour_at(-1, n, adjacent_node);
                }
                adjacent_node_name = strtok(NULL, ",");
            }
        }

        line_num++;
    }
}

/**
 * @brief It saves a graph to a csv file
 * the function exits if it failed to open the file
 * 
 * @param fpath The file to save to
 * @param g The graph to save
 */
void save_graph_to_csv(const char *fpath, const Graph *g) {
    assert(strstr(fpath, ".csv") != NULL);
    FILE *fp;
    fp = fopen(fpath, "wt");
    if (fp == NULL) {
        print_error("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < g->used; i++) {
        // print the node name, coords
        fprintf(fp, "%s;%f;%f;", g->nodes[i]->name, g->nodes[i]->coords.x, g->nodes[i]->coords.y);

        fprintf(fp, "\"");
        // print the node neighbours
        for (ListNode *neighbour = g->nodes[i]->neighbours; neighbour != NULL; neighbour = neighbour->next_node) {
            fprintf(fp, "%s%s", neighbour->node->name, neighbour->next_node != NULL ? "," : "");
        }
        fprintf(fp, "\"\n");
    }

    fclose(fp);
}
