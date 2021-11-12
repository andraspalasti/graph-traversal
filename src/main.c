#include "./c-econio/econio.h"
#include "coordinates.h"
#include "file_management.h"
#include "graph.h"
#include "node.h"
#include "path_finding.h"
#include "visualization.h"
#include <stdio.h>
#include <stdlib.h>

enum MenuState {
    IDLE = -1,
    LOAD_GRAPH = 0,
    SAVE_GRAPH = 1,
    ADD_NODE = 2,
    REMOVE_NODE = 3,
    ADD_EDGE = 4,
    REMOVE_EDGE = 5,
    DISPLAY_GRAPH = 6,
    DISPLAY_GRAPH_WITH_PATH = 7,
};

int main() {
    Graph *g = init_graph();

    enum MenuState state = IDLE;
    econio_clrscr();

    bool quit = false;

    while (quit == false) {
        switch (state) {
            case IDLE:
                econio_clrscr();
                econio_rawmode();
                // the text to be displayed for each action
                const char *menu_text[] = {"Load graph from file",
                                           "Save current graph to file",
                                           "Add node to graph",
                                           "Remove node from graph",
                                           "Add edge between nodes",
                                           "Remove edge between nodes",
                                           "Display graph",
                                           "Display shortest path between nodes", "\0"};
                int selected_action = LOAD_GRAPH;
                while (state == IDLE) {
                    int menu_length = 0;
                    for (int i = 0; strcmp(menu_text[i], "\0") != 0; i++) {
                        if (i == selected_action) {
                            econio_textbackground(COL_LIGHTBLUE);
                            econio_textcolor(COL_DARKGRAY);
                            printf("--> %s\n", menu_text[i]);
                            econio_textcolor(COL_RESET);
                            econio_textbackground(COL_RESET);
                        } else
                            printf("%-4s%s\n", "", menu_text[i]);
                        menu_length++;
                    }

                    int key = econio_getch();
                    if (key == KEY_UP)
                        selected_action = selected_action == 0 ? selected_action : selected_action - 1;
                    else if (key == KEY_DOWN)
                        selected_action = selected_action == menu_length - 1 ? selected_action : selected_action + 1;
                    else if (key == KEY_ENTER)
                        state = selected_action;
                    else if (key == KEY_ESCAPE) {
                        quit = true;
                        break;
                    }
                    econio_clrscr();
                }
                econio_normalmode();
                break;

            default:
                quit = true;
                break;
        }
    }
    econio_clrscr();

    free_graph(g);
    return 0;
}
