#ifndef CONSOLE_MENU_H
#define CONSOLE_MENU_H

#include "graph.h"

// the time to leave for the user to read the message in the console in sec
#define TIME_TO_READ_MSG 1

enum MenuState {
    QUIT = -2,
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

enum MenuState select_menu(const char *menu_items[]);

enum MenuState load_graph_menu(Graph *g);

enum MenuState save_graph_menu(const Graph *g);

Node *find_node_from_console(const Graph *g);

Node *read_node_from_console();

#endif
