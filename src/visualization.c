#include "visualization.h"
#include "sdl_helpers.h"
#include "util.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <assert.h>

/**
 * @brief Opens an SDL window and drawes the graph in it
 * 
 * @param g Graph to draw
 */
void draw_graph(Graph *g) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(SCREEN_WIDTH, SCREEN_HEIGHT, &window, &renderer);
    TTF_Font *font = ttf_init("font.ttf", 14);

    // the matrix contains what edges we have already drawn
    bool **adjacency_matrix = init_bool_matrix(g->used, g->used);
    for (int i = 0; i < g->used; i++)
        for (int j = 0; j < g->used; j++)
            adjacency_matrix[i][j] = false;

    // draw edges first so they dont overlap nodes
    for (int i = 0; i < g->used; i++) {
        ListNode *neighbour = g->nodes[i]->neighbours;
        while (neighbour != NULL) {
            // only draw an edge if we have not drawn it yet
            if (adjacency_matrix[i][neighbour->node->idx] == false) {
                // check if we can traverse edge both ways
                // then we only draw one line
                if (is_connected(neighbour->node, g->nodes[i])) {
                    draw_line_between_nodes(renderer, g->nodes[i], neighbour->node);
                    adjacency_matrix[i][neighbour->node->idx] = true;
                    adjacency_matrix[neighbour->node->idx][i] = true;
                } else {
                    draw_arrow_between_nodes(renderer, g->nodes[i], neighbour->node);
                    adjacency_matrix[i][neighbour->node->idx] = true;
                }
            }

            neighbour = neighbour->next_node;
        }
    }

    for (int i = 0; i < g->used; i++) {
        draw_node(renderer, font, g->nodes[i]);
    }

    SDL_RenderPresent(renderer);
    free_bool_matrix(adjacency_matrix);
    TTF_CloseFont(font);

    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * @brief Draws a line between the two nodes
 * 
 * @param renderer 
 * @param n1 
 * @param n2 
 */
void draw_line_between_nodes(SDL_Renderer *renderer, Node *n1, Node *n2) {
    Coordinates c1 = normalize_coords(n1->coords, SCREEN_WIDTH, SCREEN_HEIGHT);
    Coordinates c2 = normalize_coords(n2->coords, SCREEN_WIDTH, SCREEN_HEIGHT);

    Coordinates sub = subtract(c2, c1);
    double d = distance(c1, c2);
    assert(d != 0); // we should not divide by zero

    draw_line_between_coords(renderer,
                             add(scale(NODE_RADIUS / d, sub), c1),
                             add(scale((d - NODE_RADIUS) / d, sub), c1), BLACK);
}

/**
 * @brief Draws an arrow between the two nodes
 * 
 * @param renderer 
 * @param n1 The node thet the arrow starts from
 * @param n2 The node that the arrow points to
 */
void draw_arrow_between_nodes(SDL_Renderer *renderer, Node *n1, Node *n2) {
    Coordinates c1 = normalize_coords(n1->coords, SCREEN_WIDTH, SCREEN_HEIGHT);
    Coordinates c2 = normalize_coords(n2->coords, SCREEN_WIDTH, SCREEN_HEIGHT);

    Coordinates sub = subtract(c2, c1);
    double d = distance(c1, c2);
    assert(d != 0); // we should not divide by zero

    Coordinates arrow_head_start = add(scale((d - NODE_RADIUS) / d, sub), c1);
    Coordinates arrow_head_width = scale((d - NODE_RADIUS - ARROW_HEAD_LENGTH + ARROW_HEAD_WIDTH / 2.0) / d, sub);
    Coordinates arrow_head_end = scale((d - NODE_RADIUS - ARROW_HEAD_LENGTH) / d, sub);

    draw_line_between_coords(renderer, add(scale(NODE_RADIUS / d, sub), c1), arrow_head_start, BLACK);
    draw_line_between_coords(renderer,
                             add(rotate_around(arrow_head_end, arrow_head_width, PI / 2), c1),
                             arrow_head_start, BLACK);
    draw_line_between_coords(renderer,
                             add(rotate_around(arrow_head_end, arrow_head_width, -PI / 2), c1),
                             arrow_head_start, BLACK);
}

/**
 * @brief Draws a line between the to coordinates
 * 
 * @param renderer The renderer to draw to
 * @param c1 
 * @param c2 
 * @param color Color to draw with
 */
void draw_line_between_coords(SDL_Renderer *renderer, Coordinates c1, Coordinates c2, Uint32 color) {
    aalineColor(renderer, c1.x, c1.y, c2.x, c2.y, color);
}

/**
 * @brief Draws the node to the SDL renderer
 * 
 * @param renderer 
 * @param n Node to draw
 */
void draw_node(SDL_Renderer *renderer, TTF_Font *font, Node *n) {
    Coordinates pos = normalize_coords(n->coords, SCREEN_WIDTH, SCREEN_HEIGHT);
    filledCircleColor(renderer, pos.x, pos.y, NODE_RADIUS, OPACITY_60_WHITE);
    aacircleColor(renderer, pos.x, pos.y, NODE_RADIUS, BLACK);
    render_text(renderer, font, BLACK, n->name, pos);
}
