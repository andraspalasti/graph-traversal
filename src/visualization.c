#include "visualization.h"
#include "coordinates.h"
#include "draw.h"
#include "sdl_helpers.h"
#include "util.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <assert.h>
#include <stdbool.h>

void display_graph(Graph *g) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &renderer);
    TTF_Font *font = ttf_init("font.ttf", 14);

    SDL_RenderPresent(renderer);

    Uint64 START = SDL_GetPerformanceCounter();
    double delta_time = 0; // Time elapsed from start in milliseconds

    const double ANIM_DURATION = 1.5; // The duration of the animation in seconds

    SDL_Event e;
    bool quit = false;
    SDL_Color bg = hexcolor_to_sdl_color(BG_COLOR);
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r)
                START = SDL_GetPerformanceCounter();
        }

        delta_time = (double)((SDL_GetPerformanceCounter() - START) * 1000 / (double)SDL_GetPerformanceFrequency());

        SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
        SDL_RenderClear(renderer);
        if (ANIM_DURATION > delta_time * 0.001)
            draw_graph(renderer, font, g,
                       cubic_bezier(0.8, 0.8, delta_time * 0.001 / ANIM_DURATION));
        else
            draw_graph(renderer, font, g, 1.0);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
