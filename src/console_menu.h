#ifndef CONSOLE_MENU_H
#define CONSOLE_MENU_H

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

#endif
