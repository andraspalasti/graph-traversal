#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "graph.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

// COLORS
#define BG_COLOR 0xFFFFFFFF
#define TEXT_COLOR 0xF0000000
#define EDGE_COLOR 0xF0000000
#define NODE_BORDER_COLOR 0xF0000000
#define NODE_COLOR 0xAAFFFFFF

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

#define NODE_RADIUS 20
#define MARGIN 10
#define ARROW_HEAD_LENGTH 20
#define ARROW_HEAD_WIDTH 10

#define MAX_X_COORD (SCREEN_WIDTH - NODE_RADIUS - MARGIN) / 2
#define MAX_Y_COORD (SCREEN_HEIGHT - NODE_RADIUS - MARGIN) / 2

void draw_graph(Graph *g);

void draw_line_between_nodes(SDL_Renderer *renderer, Node *n1, Node *n2);

void draw_node(SDL_Renderer *renderer, TTF_Font *font, Node *n);

void draw_arrow_between_nodes(SDL_Renderer *renderer, Node *n1, Node *n2);

void draw_line_between_coords(SDL_Renderer *renderer, Coordinates c1, Coordinates c2, Uint32 color);

#endif
