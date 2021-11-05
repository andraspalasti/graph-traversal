#include "visualization.h"
#include "animations.h"
#include "coordinates.h"
#include "draw.h"
#include "path_finding.h"
#include "sdl_helpers.h"
#include "util.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <assert.h>
#include <stdbool.h>

/**
 * @brief Animates the drawing of the specified
 * graph in an SDL window
 * 
 * @param g Graph to animate
 */
void display_graph(Graph *g) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &renderer);
    TTF_Font *font = ttf_init("font.ttf", 14);

    SDL_RenderPresent(renderer);

    Uint64 START = SDL_GetPerformanceCounter();
    double delta_time = 0; // Time elapsed from start in milliseconds

    const double ANIM_DURATION = 1500; // The duration of the animation in milliseconds

    SDL_Event e;
    bool quit = false, is_finished = false;
    SDL_Color bg = hexcolor_to_sdl_color(BG_COLOR);
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;

            // if the user presses 'r' then restart the animation
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
                START = SDL_GetPerformanceCounter();
                delta_time = 0;
                is_finished = false;
            }
        }

        // if animation is over dont waste resources on drawing the same thing
        // rather check for input every 100ms
        if (is_finished) {
            // update elapsed time
            delta_time = (double)((SDL_GetPerformanceCounter() - START) * 1000 / (double)SDL_GetPerformanceFrequency());

            SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
            SDL_RenderClear(renderer);

            // need to abstract this
            if (ANIM_DURATION > delta_time)
                draw_graph(renderer, font, g, NULL,
                           cubic_bezier(0.8, 0.8, delta_time / ANIM_DURATION));
            else {
                draw_graph(renderer, font, g, NULL, 1.0);
                is_finished = true;
            }

            SDL_RenderPresent(renderer);
        } else {
            SDL_Delay(100);
        }
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * @brief Draws a graph in an SDL window and
 * animates the drawing of the specified path
 * 
 * @param g Graph to draw
 * @param p Path to animate
 */
void display_graph_with_path(Graph *g, Path *p) {
    assert(p != NULL);
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &renderer);
    TTF_Font *font = ttf_init("font.ttf", 14);

    Uint64 START = SDL_GetPerformanceCounter();
    double delta_time = 0; // Time elapsed from start in milliseconds

    const double ANIM_DURATION = 1500; // The duration of the animation in milliseconds

    SDL_Event e;
    bool quit = false;
    SDL_Color bg = hexcolor_to_sdl_color(BG_COLOR);

    // the current path which is being animated
    Path *from = p;
    Path *to = p != NULL ? p->next_node : NULL;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
                START = SDL_GetPerformanceCounter();
                delta_time = 0;
                // reset animated nodes
                from = p;
                to = p != NULL ? p->next_node : NULL;
            }
        }

        delta_time = (double)((SDL_GetPerformanceCounter() - START) * 1000 / (double)SDL_GetPerformanceFrequency());

        SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
        SDL_RenderClear(renderer);

        draw_graph(renderer, font, g, p, 1.0);

        // draw the paths that finished animating
        for (Path *i = p; i != from; i = i->next_node) {
            if (is_connected(i->next_node->node, i->node)) {
                draw_line_between_nodes(renderer, i->node->coords, i->next_node->node->coords, NODE_RADIUS, PATH_COLOR);
            } else {
                draw_arrow_between_nodes(renderer, i->node->coords, i->next_node->node->coords, NODE_RADIUS, PATH_COLOR);
            }
        }

        if (from != NULL && to != NULL) {
            double scale_factor = ANIM_DURATION > delta_time ? (delta_time / ANIM_DURATION) : 1;
            if (is_connected(to->node, from->node)) {
                draw_line_between_nodes(renderer, from->node->coords,
                                        add(scale(scale_factor, subtract(to->node->coords, from->node->coords)),
                                            from->node->coords),
                                        NODE_RADIUS, PATH_COLOR);
            } else {
                draw_arrow_between_nodes(renderer, from->node->coords,
                                         add(scale(scale_factor, subtract(to->node->coords, from->node->coords)),
                                             from->node->coords),
                                         NODE_RADIUS, PATH_COLOR);
            }
            if (delta_time >= ANIM_DURATION) {
                START = SDL_GetPerformanceCounter();
                delta_time = 0;
                from = to;
                to = to->next_node;
            }
        }

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
