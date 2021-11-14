#include "console_menu.h"
#include "coordinates.h"
#include "econio.h"
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
        switch (state) {
            case IDLE:
                state = select_menu(menu_items);
                break;

            case LOAD_GRAPH:
                state = load_graph_menu(g);
                break;

            case SAVE_GRAPH:
                state = save_graph_menu(g);
                break;

            case DISPLAY_GRAPH:
                if (g->used == 0) {
                    printf("There are no nodes in your graph to display\n");
                    econio_sleep(TIME_TO_READ_MSG);
                    state = IDLE;
                    break;
                }
                econio_clrscr();
                printf("Close the SDL window to continue\n");
                display_graph(g);
                state = IDLE;
                break;

            case DISPLAY_GRAPH_WITH_PATH:
                econio_clrscr();

                printf("Type in the node's name where the path should start from\n");
                Node *from = find_node_from_console(g);

                printf("Type in the node's name where the path should end\n");
                Node *to = find_node_from_console(g);

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
                state = IDLE;
                break;

            default:
                state = QUIT;
                break;
        }
    }
    econio_clrscr();

    free_graph(g);
    return 0;
}
