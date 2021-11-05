#include "draw.h"
#include "coordinates.h"
#include "graph.h"
#include "sdl_helpers.h"
#include "util.h"
#include "visualization.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <assert.h>

/**
 * @brief Scales the node's coordinates by scale_factor and draws the graph
 * It does not modify the graph
 * 
 * @param renderer 
 * @param font 
 * @param g 
 * @param exclude_path It will not draw these paths
 * @param scale_factor 
 */
void draw_graph(SDL_Renderer *renderer, TTF_Font *font, Graph *g, Path *exclude_path, double scale_factor) {
    // the matrix contains what edges we have already drawn
    bool **adjacency_matrix = init_bool_matrix(g->used, g->used);
    for (int i = 0; i < g->used; i++)
        for (int j = 0; j < g->used; j++)
            adjacency_matrix[i][j] = false;

    // Do not draw the paths in exclude_path
    while (exclude_path != NULL && exclude_path->next_node != NULL) {
        adjacency_matrix[exclude_path->node->idx][exclude_path->next_node->node->idx] = true;
        adjacency_matrix[exclude_path->next_node->node->idx][exclude_path->node->idx] = true;
        exclude_path = exclude_path->next_node;
    }

    // draw edges first so they dont overlap nodes
    for (int i = 0; i < g->used; i++) {
        ListNode *neighbour = g->nodes[i]->neighbours;
        while (neighbour != NULL) {
            // only draw an edge if we have not drawn it yet
            if (adjacency_matrix[i][neighbour->node->idx] == false) {
                // check if we can traverse edge both ways
                // then we only draw one line
                if (is_connected(neighbour->node, g->nodes[i])) {
                    draw_line_between_nodes(renderer,
                                            scale(scale_factor, g->nodes[i]->coords),
                                            scale(scale_factor, neighbour->node->coords), NODE_RADIUS, EDGE_COLOR);
                    adjacency_matrix[i][neighbour->node->idx] = true;
                    adjacency_matrix[neighbour->node->idx][i] = true;
                } else {
                    draw_arrow_between_nodes(renderer,
                                             scale(scale_factor, g->nodes[i]->coords),
                                             scale(scale_factor, neighbour->node->coords), NODE_RADIUS, EDGE_COLOR);
                    adjacency_matrix[i][neighbour->node->idx] = true;
                }
            }

            neighbour = neighbour->next_node;
        }
    }

    for (int i = 0; i < g->used; i++) {
        draw_node(renderer, font, g->nodes[i], NODE_RADIUS);
    }
    free_bool_matrix(adjacency_matrix);
}

/**
 * @brief Draws a line between the two nodes
 * 
 * @param renderer 
 * @param n1 Coordinates of node
 * @param n2 Coordinates of node
 */
void draw_line_between_nodes(SDL_Renderer *renderer, Coordinates n1, Coordinates n2, double node_radius, Uint32 color) {
    Coordinates c1 = normalize_coords(n1, SCREEN_WIDTH, SCREEN_HEIGHT);
    Coordinates c2 = normalize_coords(n2, SCREEN_WIDTH, SCREEN_HEIGHT);

    Coordinates sub = subtract(c2, c1);
    double d = distance(c1, c2);
    assert(d != 0); // we should not divide by zero

    draw_line_between_coords(renderer,
                             add(scale(node_radius / d, sub), c1),
                             add(scale((d - node_radius) / d, sub), c1), color);
}

/**
 * @brief Draws an arrow between the two nodes
 * 
 * @param renderer 
 * @param n1 The node's coords that the arrow starts from
 * @param n2 The node's coords that the arrow points to
 */
void draw_arrow_between_nodes(SDL_Renderer *renderer, Coordinates n1, Coordinates n2, double node_radius, Uint32 color) {
    Coordinates c1 = normalize_coords(n1, SCREEN_WIDTH, SCREEN_HEIGHT);
    Coordinates c2 = normalize_coords(n2, SCREEN_WIDTH, SCREEN_HEIGHT);

    Coordinates sub = subtract(c2, c1);
    double d = distance(c1, c2);
    assert(d != 0); // we should not divide by zero

    Coordinates arrow_head_start = add(scale((d - node_radius) / d, sub), c1);
    Coordinates arrow_head_width = scale((d - node_radius - ARROW_HEAD_LENGTH + ARROW_HEAD_WIDTH / 2.0) / d, sub);
    Coordinates arrow_head_end = scale((d - node_radius - ARROW_HEAD_LENGTH) / d, sub);

    draw_line_between_coords(renderer, add(scale(node_radius / d, sub), c1), arrow_head_start, color);
    draw_line_between_coords(renderer,
                             add(rotate_around(arrow_head_end, arrow_head_width, PI / 2), c1),
                             arrow_head_start, color);
    draw_line_between_coords(renderer,
                             add(rotate_around(arrow_head_end, arrow_head_width, -PI / 2), c1),
                             arrow_head_start, color);
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
void draw_node(SDL_Renderer *renderer, TTF_Font *font, Node *n, double node_radius) {
    Coordinates pos = normalize_coords(n->coords, SCREEN_WIDTH, SCREEN_HEIGHT);
    filledCircleColor(renderer, pos.x, pos.y, node_radius, NODE_COLOR);
    aacircleColor(renderer, pos.x, pos.y, node_radius, NODE_BORDER_COLOR);
    render_text(renderer, font, TEXT_COLOR, n->name, pos);
}
