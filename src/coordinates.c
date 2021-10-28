#include "coordinates.h"
#include <math.h>
#include <stdio.h>

/**
 * @brief Prints the formated coords
 * 
 * @param coords 
 */
void print_coords(Coordinates coords) {
    printf("(%g, %g)\n", coords.x, coords.y);
}

/**
 * @brief Returns the distance between the specified nodes
 * 
 * @param a 
 * @param b 
 * @return double 
 */
double distance(Coordinates a, Coordinates b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
