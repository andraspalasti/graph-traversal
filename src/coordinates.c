#include "coordinates.h"
#include <math.h>
#include <stdio.h>

void print_coords(Coordinates coords) {
    printf("(%d, %d)\n", coords.x, coords.y);
}

/*
* Returns the distance between the specified coordinates
*/
double distance(Coordinates a, Coordinates b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
