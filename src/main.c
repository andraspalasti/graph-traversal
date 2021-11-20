#include "../include/debugmalloc.h"
#include "../include/econio.h"
#include "console_menu.h"
#include "coordinates.h"
#include "file_management.h"
#include "graph.h"
#include "node.h"
#include "path_finding.h"
#include "util.h"
#include "visualization.h"
#include <stdio.h>
#include <stdlib.h>

// the text to be displayed for menu item
const char *menu_items[] = {"Load graph from file",
                            "Save current graph to file",
                            "Add node to graph",
                            "Remove node from graph",
                            "Add edge between nodes",
                            "Remove edge between nodes",
                            "Display graph",
                            "Display shortest path between nodes", "\0"};

int main() {
    Graph *g = init_graph();

    enum MenuState state = IDLE;
    econio_clrscr();

    while (state != QUIT) {
        Node *from, *to;
        char answer[4];

        switch (state) {
            case IDLE:
                econio_clrscr();
                state = select_menu(menu_items);
                break;

            case LOAD_GRAPH:
                state = load_graph_menu(g);
                break;

            case SAVE_GRAPH:
                state = save_graph_menu(g);
                break;

            case ADD_NODE:
                econio_clrscr();
                Node *new_node = read_node_from_console();
                add_node_to_graph(g, new_node);

                econio_textcolor(COL_GREEN);
                printf("You successfully created the node\n");
                econio_sleep(TIME_TO_READ_MSG);
                econio_textcolor(COL_RESET);

                state = IDLE;
                break;

            case REMOVE_NODE:
                econio_clrscr();
                printf("Type in the node's name that you want to delete\n");
                Node *to_be_deleted = find_node_from_console(g);
                delete_node_from_graph(g, to_be_deleted);
                econio_textcolor(COL_GREEN);
                printf("You successfully deleted the node\n");
                econio_sleep(TIME_TO_READ_MSG);
                econio_textcolor(COL_RESET);

                state = IDLE;
                break;

            case ADD_EDGE:
                econio_clrscr();
                printf("Type in the node's name where the edge would start from\n");
                from = find_node_from_console(g);

                printf("Type in the node's name where the edge would end\n");
                to = find_node_from_console(g);

                printf("Is this edge directional ? (default is no) [yes/no]\n");
                read_str(answer, 3);
                add_neighbour_at(0, from, to);
                if (strcmp(answer, "yes") != 0) {
                    add_neighbour_at(0, to, from);
                }

                econio_textcolor(COL_GREEN);
                printf("Successfully added edge between nodes %s and %s\n", from->name, to->name);
                econio_sleep(TIME_TO_READ_MSG);
                econio_textcolor(COL_RESET);

                state = IDLE;
                break;

            case REMOVE_EDGE:
                econio_clrscr();
                printf("Type in the node's name where the edge starts from\n");
                from = find_node_from_console(g);

                printf("Type in the node's name where the edge ends\n");
                to = find_node_from_console(g);

                printf("Should I delete the edge both ways ? (default is yes) [yes/no]\n");
                read_str(answer, 3);
                remove_neighbour(from, to);
                if (strcmp(answer, "no") != 0) {
                    remove_neighbour(to, from);
                }

                econio_textcolor(COL_GREEN);
                printf("Successfully deleted edge between nodes %s and %s\n", from->name, to->name);
                econio_sleep(TIME_TO_READ_MSG);
                econio_textcolor(COL_RESET);
                state = IDLE;
                break;

            case DISPLAY_GRAPH:
                econio_clrscr();
                if (g->used == 0) {
                    printf("There are no nodes in your graph to display\n");
                    econio_sleep(TIME_TO_READ_MSG);
                    state = IDLE;
                    break;
                }
                printf("Close the SDL window to continue\n");
                display_graph(g);
                state = IDLE;
                break;

            case DISPLAY_GRAPH_WITH_PATH:
                econio_clrscr();

                printf("Type in the node's name where the path should start from\n");
                from = find_node_from_console(g);

                printf("Type in the node's name where the path should end\n");
                to = find_node_from_console(g);

                Path *p = find_path(g, from, to);
                if (p == NULL) {
                    print_error("There is no path between the specified nodes\n");
                    econio_sleep(1);
                    state = IDLE;
                    break;
                }

                econio_clrscr();
                printf("Close the SDL window to continue\n");
                display_graph_with_path(g, p);
                free_path(p);
                state = IDLE;
                break;

            default:
                state = QUIT;
                break;
        }
    }
    // econio_clrscr();
    free_graph(g);
    return 0;
}
