#include "console_menu.h"
#include "econio.h"
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
            selected_action = selected_action == 0 ? selected_action : selected_action - 1;
        else if (key == KEY_DOWN)
            selected_action = selected_action == menu_length - 1 ? selected_action : selected_action + 1;
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
