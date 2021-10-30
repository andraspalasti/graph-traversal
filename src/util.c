#include "util.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Instantiates a new SDL window and renderer 
 * and checks for errors
 * 
 * @param width Width of window
 * @param height Height of window
 * @param pwindow 
 * @param prenderer 
 */
void sdl_init(int width, int height, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    assert(width > 0 && height > 0);
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        print_error("Could not start SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // maybe we need to extract the title into a variable or a param
    SDL_Window *window = SDL_CreateWindow("Graph Traversal",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        print_error("Could not create window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        print_error("Could not create renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

/**
 * @brief Opens the specified font file and 
 * instantiates a new TTF_Font with the specified font size
 * 
 * @param ttf_file Path to font file
 * @param font_size
 * @return TTF_Font* 
 */
TTF_Font *ttf_init(const char *ttf_file, int font_size) {
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(ttf_file, font_size);
    if (!font) {
        print_error("Could not open font: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    return font;
}

/**
 * @brief The function splits the string by the separator into an array of pointers
 * ATTENTION: this function modifies str
 * 
 * @param str
 * @param parts
 * @param num_of_splits 
 * @param sep 
 */
void split(char *str, char *parts[], int num_of_splits, const char *sep) {
    assert(num_of_splits > 0);
    parts[0] = strtok(str, sep);
    for (int i = 1; i < num_of_splits; i++) {
        parts[i] = strtok(NULL, sep);
    }
}

/**
 * @brief if the ptr is null than prints an error message and exits
 * 
 * @param ptr 
 */
void check_malloc(void *ptr) {
    if (ptr == NULL) {
        print_error("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Removes all occurences of the specified char in str
 * 
 * @param str 
 * @param char_to_remove 
 */
void remove_chars(char *str, char char_to_remove) {
    int i, j;
    int len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == char_to_remove) {
            for (j = i; j < len; j++) {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }
}

/**
 * @brief Prints the message to the console in red and prefixis it with ERROR:
 * 
 */
__attribute__((format(printf, 1, 2))) void print_error(const char *format, ...) {
    va_list arg;
    va_start(arg, format);

    printf(BOLDRED "ERROR: ");
    vprintf(format, arg);
    printf(RESET);

    va_end(arg);
}
