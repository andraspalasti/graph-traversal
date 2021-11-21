#include "coordinates.h"
#include "../include/debugmalloc.h"
#include <assert.h>
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
 * @brief Returns the distance between the specified coords
 * 
 * @param a 
 * @param b 
 * @return double 
 */
double distance(Coordinates a, Coordinates b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

/**
 * @brief Normalize coordinates into an all positive coordinate system
 * 
 * @param coords The coords to normalize
 * @param width Width of avilable space
 * @param height Height of avilable space
 * @return Coordinates The normalized coordinates
 */
Coordinates normalize_coords(Coordinates coords, int width, int height) {
    coords.x += (double)width / 2.0;
    coords.y = (double)height / 2.0 - coords.y;
    return coords;
}

/**
 * @brief Scales the coordinates by the specified lambda
 * 
 * @param lambda The factor to scale with
 * @param coords The coordinates to scale
 * @return Coordinates The scaled coordinates
 */
Coordinates scale(double lambda, Coordinates coords) {
    coords.x *= lambda;
    coords.y *= lambda;
    return coords;
}

/**
 * @brief Rotates the specified coords around the specified origin
 * 
 * @param origin The origin to rotate around
 * @param coords The coords to rotate
 * @param alpha The angle to rotate by
 * @return Coordinates The rotated coordinates
 */
Coordinates rotate_around(Coordinates origin, Coordinates coords, double alpha) {
    Coordinates sub = subtract(coords, origin);
    double cos_a = cos(alpha);
    double sin_a = sin(alpha);
    return (Coordinates){.x = sub.x * cos_a - sub.y * sin_a + origin.x,
                         .y = sub.y * cos_a + sub.x * sin_a + origin.y};
}

/**
 * @brief Sums the two coordinates
 * 
 * @param c1 
 * @param c2 
 * @return Coordinates 
 */
Coordinates add(Coordinates c1, Coordinates c2) {
    c1.x += c2.x;
    c1.y += c2.y;
    return c1;
}

/**
 * @brief Subtracts the two coordinates
 * 
 * @param c1 Coordinate to subtract from
 * @param c2 
 * @return Coordinates 
 */
Coordinates subtract(Coordinates c1, Coordinates c2) {
    c1.x -= c2.x;
    c1.y -= c2.y;
    return c1;
}
