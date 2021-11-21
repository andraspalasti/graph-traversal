#ifndef DRAW_H
#define DRAW_H

#include "../graph.h"
#include "../path_finding.h"
#include <SDL.h>
#include <SDL_ttf.h>

void draw_graph(SDL_Renderer *renderer, TTF_Font *font, const Graph *g);

void draw_line_between_nodes(SDL_Renderer *renderer, const Node *n1, const Node *n2, double node_radius, Uint32 color);

void draw_arrow_between_nodes(SDL_Renderer *renderer, const Node *n1, const Node *n2, double node_radius, Uint32 color);

void draw_line(SDL_Renderer *renderer, Coordinates c1, Coordinates c2, Uint32 color);

void draw_arrow(SDL_Renderer *renderer, Coordinates from, Coordinates to, Uint32 color);

void draw_node(SDL_Renderer *renderer, TTF_Font *font, const Node *n, double node_radius);

void get_vector(Coordinates *vector, const Node *n1, const Node *n2, double node_radius);

#endif
