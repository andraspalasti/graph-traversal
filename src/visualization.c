#include "visualization.h"
#include "../include/debugmalloc.h"
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
    assert(g != NULL);

    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &renderer);
    TTF_Font *font = ttf_init("font.ttf", 14);

    SDL_RenderPresent(renderer);

    Animation *anim = init_animation(1500);

    SDL_Event e;
    bool quit = false;
    SDL_Color bg = hexcolor_to_sdl_color(BG_COLOR);
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;

            // if the user presses 'r' then restart the animation
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
                restart_animation(anim);
            }
        }

        // if animation is over dont waste resources on drawing the same thing
        // rather check for input every 100ms
        if (anim->is_finished == false) {
            update_animation(anim); // anim->is_finished can change here

            SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
            SDL_RenderClear(renderer);

            if (!anim->is_finished) {
                // scale graph down
                for (int i = 0; i < g->used; i++)
                    g->nodes[i]->coords = scale(anim->delta_time / anim->ANIM_DURATION, g->nodes[i]->coords);
            }

            draw_graph(renderer, font, g);

            if (!anim->is_finished) {
                // scale graph back to original size
                for (int i = 0; i < g->used; i++)
                    g->nodes[i]->coords = scale(anim->ANIM_DURATION / anim->delta_time, g->nodes[i]->coords);
            }
            SDL_RenderPresent(renderer);
        } else {
            SDL_Delay(100);
        }
    }

    free_animation(anim);
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
    assert(p != NULL && p->next_node != NULL);

    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &renderer);
    TTF_Font *font = ttf_init("font.ttf", 14);

    Animation *anim = init_animation(1000); // the time till one edge is drawn from path

    SDL_Event e;
    bool quit = false;
    SDL_Color bg = hexcolor_to_sdl_color(BG_COLOR);

    // remove the specified path from the graph
    // so our draw_graph function will not draw it
    // we will add these paths back at the end of the function
    bool *is_directed = malloc(list_node_len(p) * sizeof(bool));
    int i = 0;
    for (Path *cur_p = p; cur_p != NULL && cur_p->next_node != NULL; cur_p = cur_p->next_node) {
        is_directed[i] = is_connected(cur_p->next_node->node, cur_p->node);
        if (is_directed[i]) {
            remove_neighbour(cur_p->node, cur_p->next_node->node);
            remove_neighbour(cur_p->next_node->node, cur_p->node);
        } else
            remove_neighbour(cur_p->node, cur_p->next_node->node);
        i++;
    }

    Path *animated_path = p; // the path that is currently animating
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
                restart_animation(anim);
                animated_path = p; // reset the currently animating path
            }
        }

        if (anim->is_finished == false) {
            update_animation(anim);

            SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
            SDL_RenderClear(renderer);

            draw_graph(renderer, font, g);

            // draw the paths that already finished animating
            for (Path *drawn_path = p; drawn_path != animated_path; drawn_path = drawn_path->next_node) {
                draw_arrow_between_nodes(renderer, drawn_path->node, drawn_path->next_node->node, NODE_RADIUS, PATH_COLOR);
            }

            if (animated_path != NULL && animated_path->next_node != NULL) {
                double scale_factor = anim->is_finished ? 1 : (anim->delta_time / anim->ANIM_DURATION);
                Coordinates vector[2];
                get_vector(vector, animated_path->node, animated_path->next_node->node, NODE_RADIUS);

                draw_arrow(renderer, vector[0],
                           add(scale(scale_factor, subtract(vector[1], vector[0])), vector[0]),
                           PATH_COLOR);

                // restart animation and jump to next path to animate
                if (anim->is_finished) {
                    restart_animation(anim);
                    animated_path = animated_path->next_node;
                }
            }

            SDL_RenderPresent(renderer);

        } else {
            SDL_Delay(100);
        }
    }

    // we need to put back the path that we extracted from the graph
    int j = 0;
    for (Path *cur_p = p; cur_p != NULL && cur_p->next_node != NULL; cur_p = cur_p->next_node) {
        if (is_directed[j]) {
            add_neighbour_at(0, cur_p->node, cur_p->next_node->node);
            add_neighbour_at(0, cur_p->next_node->node, cur_p->node);
        } else
            add_neighbour_at(0, cur_p->node, cur_p->next_node->node);
        j++;
    }

    free(is_directed);
    free_animation(anim);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
