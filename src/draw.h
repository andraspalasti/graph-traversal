#ifndef DRAW_H
#define DRAW_H

#include "graph.h"
#include "path_finding.h"
#include <SDL.h>
#include <SDL_ttf.h>

void draw_graph(SDL_Renderer *renderer, TTF_Font *font, Graph *g, Path *exclude_path, double scale_factor);

void draw_line_between_nodes(SDL_Renderer *renderer, Coordinates n1, Coordinates n2, double node_radius, Uint32 color);

void draw_node(SDL_Renderer *renderer, TTF_Font *font, Node *n, double node_radius);

void draw_arrow_between_nodes(SDL_Renderer *renderer, Coordinates n1, Coordinates n2, double node_radius, Uint32 color);

void draw_line_between_coords(SDL_Renderer *renderer, Coordinates c1, Coordinates c2, Uint32 color);

#endif
