#ifndef DRAW_H
#define DRAW_H

#include "graph.h"
#include <SDL.h>
#include <SDL_ttf.h>

void draw_graph(SDL_Renderer *renderer, TTF_Font *font, Graph *g, double scale_factor);

void draw_line_between_nodes(SDL_Renderer *renderer, Node *n1, Node *n2, double node_radius);

void draw_node(SDL_Renderer *renderer, TTF_Font *font, Node *n, double node_radius);

void draw_arrow_between_nodes(SDL_Renderer *renderer, Node *n1, Node *n2, double node_radius);

void draw_line_between_coords(SDL_Renderer *renderer, Coordinates c1, Coordinates c2, Uint32 color);

#endif
