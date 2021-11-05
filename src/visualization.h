#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "graph.h"
#include "path_finding.h"
#include <SDL.h>
#include <SDL_ttf.h>

// COLORS
#define BG_COLOR 0xFFFFFFFF
#define TEXT_COLOR 0xE0000000
#define EDGE_COLOR 0xE0000000
#define NODE_BORDER_COLOR 0xE0000000
#define NODE_COLOR 0xAAFFFFFF
#define PATH_COLOR 0xFF0011FF

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

#define NODE_RADIUS 20
#define MARGIN 10
#define ARROW_HEAD_LENGTH 20
#define ARROW_HEAD_WIDTH 10

#define MAX_X_COORD (SCREEN_WIDTH - NODE_RADIUS - MARGIN) / 2
#define MAX_Y_COORD (SCREEN_HEIGHT - NODE_RADIUS - MARGIN) / 2

void display_graph(Graph *g);

void display_graph_with_path(Graph *g, Path *p);

#endif
