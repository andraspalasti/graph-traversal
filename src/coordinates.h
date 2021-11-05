#ifndef COORDINATES_H
#define COORDINATES_H

#define PI 3.141592653589793

typedef struct Coordinates {
    double x, y;
} Coordinates;

void print_coords(Coordinates coords);

double distance(Coordinates a, Coordinates b);

Coordinates normalize_coords(Coordinates coords, int width, int height);

Coordinates scale(double lambda, Coordinates coords);

Coordinates rotate_around(Coordinates origin, Coordinates coords, double alpha);

Coordinates subtract(Coordinates c1, Coordinates c2);

Coordinates add(Coordinates c1, Coordinates c2);

#endif
