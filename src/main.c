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

            default:
                state = QUIT;
                break;
        }
    }
    econio_clrscr();

    free_graph(g);
    return 0;
}
