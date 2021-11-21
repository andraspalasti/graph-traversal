#ifndef SDL_HELPERS
#define SDL_HELPERS

#include "../coordinates.h"
#include <SDL.h>
#include <SDL_ttf.h>

void sdl_init(int width, int height, SDL_Window **pwindow, SDL_Renderer **prenderer);

TTF_Font *ttf_init(const char *ttf_file, int font_size);

void render_text(SDL_Renderer *renderer, TTF_Font *font, Uint32 color, const char *text, Coordinates coords);

SDL_Color hexcolor_to_sdl_color(Uint32 color);

#endif
