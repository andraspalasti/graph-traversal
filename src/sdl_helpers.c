#include "sdl_helpers.h"
#include "coordinates.h"
#include "util.h"
#include "visualization.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <assert.h>

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
    SDL_Color bg = hexcolor_to_sdl_color(BG_COLOR);
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);

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
 * @brief Renders text to the renderer at the specified coords
 * It automatically aligns the text to the center
 * 
 * @param renderer 
 * @param font The font to use
 * @param color Color of the text
 * @param text The text to render
 * @param coords The position where the text will be rendered
 */
void render_text(SDL_Renderer *renderer, TTF_Font *font, Uint32 color, const char *text, Coordinates coords) {
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect pos = {0, 0, 0, 0};

    text_surface = TTF_RenderUTF8_Blended(font, text, hexcolor_to_sdl_color(color));
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    pos.x = coords.x - text_surface->w / 2;
    pos.y = coords.y - text_surface->h / 2;
    pos.w = text_surface->w;
    pos.h = text_surface->h;
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

/**
 * @brief Converts a Uint32 hexcolor to an SDL_Color struct
 * 
 * @param color 
 * @return SDL_Color 
 */
SDL_Color hexcolor_to_sdl_color(Uint32 color) {
    Uint8 *c = (Uint8 *)&color;
    return (SDL_Color){.r = c[0], .g = c[1], .b = c[2], .a = c[3]};
}
