#include "console_menu.h"
#include "../include/debugmalloc.h"
#include "../include/econio.h"
#include "file_management.h"
#include "graph.h"
#include "node.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief This function clears the console and draws the menu 
 * with the specified menu items
 * It also creates an environment in the console where you can
 * select one of the actions from the console and it returns
 * the selected menu state
 * 
 * @param menu_items Has to be an array of strings that is terminated by null terminator
 * @return enum MenuState The selected menu state
 */
enum MenuState select_menu(const char *menu_items[]) {
    econio_clrscr();
    int selected_action = LOAD_GRAPH;
    econio_rawmode();
    while (true) {
        int menu_length = 0;
        for (int i = 0; strcmp(menu_items[i], "\0") != 0; i++) {
            if (i == selected_action) {
                econio_textbackground(COL_LIGHTBLUE);
                econio_textcolor(COL_DARKGRAY);
                printf("--> %s\n", menu_items[i]);
                econio_textcolor(COL_RESET);
                econio_textbackground(COL_RESET);
            } else
                printf("%-4s%s\n", "", menu_items[i]);
            menu_length++;
        }

        int key = econio_getch();
        if (key == KEY_UP)
            selected_action = selected_action == 0 ? menu_length - 1 : selected_action - 1;
        else if (key == KEY_DOWN)
            selected_action = selected_action == menu_length - 1 ? 0 : selected_action + 1;
        else if (key == KEY_ENTER)
            break;
        else if (key == KEY_ESCAPE) {
            selected_action = QUIT;
            break;
        }
        econio_clrscr();
    }
    econio_normalmode();
    return (enum MenuState)selected_action;
}

/**
 * @brief It asks the user to type in a file path from
 * which we can read the graph
 * If we found the file we parse it and load the data into the graph
 * 
 * @param g The graph to load the file into
 * @return enum MenuState The new menu state
 */
enum MenuState load_graph_menu(Graph *g) {
    econio_clrscr();
    printf("Type cancel to cancel action\n");
    printf("What is the path of the file that you want to read from ? (the file path is at max 128 chars)\n");
    char fpath[128 + 1];
    read_str(fpath, 128);
    if (strcmp(fpath, "cancel") == 0) {
        return IDLE;
    }

    if (strstr(fpath, ".csv") == NULL) {
        print_error("The file has to be a csv file\n");
        econio_sleep(TIME_TO_READ_MSG);
        return LOAD_GRAPH;
    } else {
        int prev_len = g->used; // the number of nodes in graph before reading the file
        read_graph_from_csv(fpath, g);
        econio_textcolor(COL_GREEN);
        printf("Successfully read %d nodes\n", g->used - prev_len);
        econio_sleep(TIME_TO_READ_MSG);
        econio_textcolor(COL_RESET);
        return IDLE;
    }
}

/**
 * @brief Asks the user to specify the file path to save the graph to
 * 
 * @param g The graph to save
 * @return enum MenuState The new menu state
 */
enum MenuState save_graph_menu(const Graph *g) {
    econio_clrscr();
    printf("Type cancel to cancel action\n");
    printf("What is the path of the file that you want to save to ? (the file path is at max 128 chars)\n");
    char fpath[128 + 1];
    read_str(fpath, 128);
    if (strcmp(fpath, "cancel") == 0) {
        return IDLE;
    }

    if (strstr(fpath, ".csv") == NULL) {
        print_error("The file has to be a csv file\n");
        econio_sleep(TIME_TO_READ_MSG);
        return SAVE_GRAPH;
    } else {
        save_graph_to_csv(fpath, g);
        econio_textcolor(COL_GREEN);
        printf("Successfully saved graph to file: %s\n", fpath);
        econio_sleep(TIME_TO_READ_MSG);
        econio_textcolor(COL_RESET);
        return IDLE;
    }
}

/**
 * @brief It asks for a node's name from the console
 * and searches for that node in the graph
 * If it finds the node it returns it
 * Else it asks the user to type it in again
 * 
 * @param g The graph to search in
 * @return Node* The specified node
 */
Node *find_node_from_console(const Graph *g) {
    char node_name[NODE_NAME_LEN + 1];

    read_str(node_name, NODE_NAME_LEN);
    Node *node = find_node(g, node_name);
    while (node == NULL) {
        print_error("Could not find the specified node in graph\n");
        read_str(node_name, NODE_NAME_LEN);
        node = find_node(g, node_name);
    }
    return node;
}
