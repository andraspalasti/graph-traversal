#include "draw.h"
#include "../include/debugmalloc.h"
#include "coordinates.h"
#include "graph.h"
#include "sdl_helpers.h"
#include "util.h"
#include "visualization.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <assert.h>

/**
 * @brief It draws the specified graph to the renderer
 * 
 * @param renderer The renderer to draw to
 * @param font The font to use
 * @param g The graph to draw
 */
void draw_graph(SDL_Renderer *renderer, TTF_Font *font, const Graph *g) {
    assert(g != NULL);
    assert(renderer != NULL);
    assert(font != NULL);

    // the nodes that already have every edge drawn
    bool *drawn_nodes = calloc(g->used, sizeof(bool));
    check_malloc(drawn_nodes);

    // draw edges first so they dont overlap nodes
    for (int i = 0; i < g->used; i++) {
        ListNode *neighbour = g->nodes[i]->neighbours;
        while (neighbour != NULL) {
            bool is_directed = is_connected(neighbour->node, g->nodes[i]);

            if (is_directed && drawn_nodes[neighbour->node->idx] == false) {
                draw_line_between_nodes(renderer, g->nodes[i], neighbour->node, NODE_RADIUS, EDGE_COLOR);
            } else if (!is_directed) {
                draw_arrow_between_nodes(renderer, g->nodes[i], neighbour->node, NODE_RADIUS, EDGE_COLOR);
            }

            neighbour = neighbour->next_node;
        }
        // mark this node as drawn
        drawn_nodes[i] = true;
    }

    for (int i = 0; i < g->used; i++) {
        draw_node(renderer, font, g->nodes[i], NODE_RADIUS);
    }
    free(drawn_nodes);
}

/**
 * @brief Draws a line between the two nodes
 * 
 * @param renderer 
 * @param n1 
 * @param n2 
 */
void draw_line_between_nodes(SDL_Renderer *renderer, const Node *n1, const Node *n2, double node_radius, Uint32 color) {
    Coordinates vector[2];
    get_vector(vector, n1, n2, node_radius);
    draw_line(renderer, vector[0], vector[1], color);
}

/**
 * @brief Draws an arrow between the two nodes
 * 
 * @param renderer 
 * @param n1 The node that the arrow starts from
 * @param n2 The node that the arrow points to
 */
void draw_arrow_between_nodes(SDL_Renderer *renderer, const Node *n1, const Node *n2, double node_radius, Uint32 color) {
    Coordinates vector[2];
    get_vector(vector, n1, n2, node_radius);
    draw_arrow(renderer, vector[0], vector[1], color);
}

/**
 * @brief Draws a line between the two coordinates
 * 
 * @param renderer The renderer to draw to
 * @param c1 
 * @param c2 
 * @param color Color to draw with
 */
void draw_line(SDL_Renderer *renderer, Coordinates c1, Coordinates c2, Uint32 color) {
    aalineColor(renderer, c1.x, c1.y, c2.x, c2.y, color);
}

/**
 * @brief Draws an arrow
 * 
 * @param renderer 
 * @param from The arrow starts from here
 * @param to 
 * @param color 
 */
void draw_arrow(SDL_Renderer *renderer, Coordinates from, Coordinates to, Uint32 color) {
    Coordinates sub = subtract(to, from);
    double d = distance(from, to);
    assert(d != 0); // we should not divide by zero

    Coordinates arrow_head_width = scale((d - ARROW_HEAD_LENGTH + ARROW_HEAD_WIDTH / 2.0) / d, sub);
    Coordinates arrow_head_end = scale((d - ARROW_HEAD_LENGTH) / d, sub);

    // draw line connecting the two points
    draw_line(renderer, from, to, color);

    // draw arrow head on the second point
    draw_line(renderer,
              add(rotate_around(arrow_head_end, arrow_head_width, PI / 2), from),
              to, color);
    draw_line(renderer,
              add(rotate_around(arrow_head_end, arrow_head_width, -PI / 2), from),
              to, color);
}

/**
 * @brief Draws a node on the renderer with the specified params
 * 
 * @param renderer 
 * @param font 
 * @param n 
 * @param node_radius 
 */
void draw_node(SDL_Renderer *renderer, TTF_Font *font, const Node *n, double node_radius) {
    Coordinates pos = normalize_coords(n->coords, SCREEN_WIDTH, SCREEN_HEIGHT);
    filledCircleColor(renderer, pos.x, pos.y, node_radius, NODE_COLOR);
    aacircleColor(renderer, pos.x, pos.y, node_radius, NODE_BORDER_COLOR);
    render_text(renderer, font, TEXT_COLOR, n->name, pos);
}

/**
 * @brief Get the vector that connects the two nodes
 * 
 * @param vector Has to be a coordinates array with length 2
 * @param n1 From
 * @param n2 To
 * @param node_radius 
 */
void get_vector(Coordinates *vector, const Node *n1, const Node *n2, double node_radius) {
    Coordinates c1 = normalize_coords(n1->coords, SCREEN_WIDTH, SCREEN_HEIGHT);
    Coordinates c2 = normalize_coords(n2->coords, SCREEN_WIDTH, SCREEN_HEIGHT);

    Coordinates sub = subtract(c2, c1);
    double d = distance(c1, c2);
    assert(d != 0); // we should not divide by zero

    vector[0] = add(scale(node_radius / d, sub), c1);
    vector[1] = add(scale((d - node_radius) / d, sub), c1);
}
