#include "visualization.h"
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

    //for (int i = 0; i < g->used; i++) {
    // ListNode *neighbour = g->nodes[1]->neighbours;
    // while (neighbour != NULL) {
    // draw_line_between_nodes(renderer, g->nodes[1], neighbour->node);
    // neighbour = neighbour->next_node;
    // }
    // draw_arrow_between_nodes(renderer, g->nodes[1], g->nodes[1]->neighbours->node);
    // draw_node(renderer, font, g->nodes[1]);
    // draw_node(renderer, font, g->nodes[1]->neighbours->node);
    // }

    SDL_RenderPresent(renderer);
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
    draw_line_between_coords(renderer, c1, c2, BLACK);
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

    Coordinates arrow_head_start = scale((d - NODE_RADIUS) / d, sub);
    Coordinates arrow_head_width = scale((d - NODE_RADIUS - ARROW_HEAD_LENGTH + ARROW_HEAD_WIDTH / 2.0) / d, sub);
    Coordinates arrow_head_end = scale((d - NODE_RADIUS - ARROW_HEAD_LENGTH) / d, sub);

    draw_line_between_coords(renderer, c1, c2, BLACK);
    draw_line_between_coords(renderer,
                             add(rotate_around(arrow_head_end, arrow_head_width, PI / 2), c1),
                             add(arrow_head_start, c1), BLACK);
    draw_line_between_coords(renderer,
                             add(rotate_around(arrow_head_end, arrow_head_width, -PI / 2), c1),
                             add(arrow_head_start, c1), BLACK);
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
 * @brief Renders text to the renderer at the specified coords
 * It automatically aligns the text to the center
 * 
 * @param renderer 
 * @param font The font to use
 * @param color Color of the text
 * @param text The text to render
 * @param coords The position where the text will be rendered
 */
void render_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, const char *text, Coordinates coords) {
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect pos = {0, 0, 0, 0};

    text_surface = TTF_RenderUTF8_Blended(font, text, color);
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
 * @brief Draws the node to the SDL renderer
 * 
 * @param renderer 
 * @param n Node to draw
 */
void draw_node(SDL_Renderer *renderer, TTF_Font *font, Node *n) {
    Coordinates pos = normalize_coords(n->coords, SCREEN_WIDTH, SCREEN_HEIGHT);
    filledCircleColor(renderer, pos.x, pos.y, NODE_RADIUS, WHITE);
    aacircleColor(renderer, pos.x, pos.y, NODE_RADIUS, BLACK);
    SDL_Color black = {.r = 0, .g = 0, .b = 0, .a = 255};
    render_text(renderer, font, black, n->name, pos);
}
