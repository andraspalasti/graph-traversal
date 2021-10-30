#ifndef UTIL_H
#define UTIL_H

#include <SDL.h>
#include <SDL_ttf.h>

#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"

void sdl_init(int width, int height, SDL_Window **pwindow, SDL_Renderer **prenderer);

TTF_Font *ttf_init(const char *ttf_file, int font_size);

void split(char *str, char *parts[], int num_of_splits, const char *sep);

void check_malloc(void *ptr);

void remove_chars(char *str, char char_to_remove);

void print_error(const char *format, ...);

#endif
