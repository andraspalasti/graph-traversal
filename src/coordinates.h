#ifndef COORDINATES_H
#define COORDINATES_H

typedef struct Coordinates {
    double x, y;
} Coordinates;

/*
* Prints a graph to the console
*/
void print_coords(Coordinates coords);

/*
* Returns the distance between the specified coordinates
*/
double distance(Coordinates a, Coordinates b);

#endif
