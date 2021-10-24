#ifndef COORDINATES_H_
#define COORDINATES_H_

typedef struct Coordinates {
    int x, y;
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
