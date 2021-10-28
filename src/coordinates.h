#ifndef COORDINATES_H
#define COORDINATES_H

typedef struct Coordinates {
    double x, y;
} Coordinates;

void print_coords(Coordinates coords);

double distance(Coordinates a, Coordinates b);

#endif
