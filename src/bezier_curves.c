#include "bezier_curves.h"

double cubic_bezier(double p0, double p1, double p2, double p3, double t) {
    return (1 - t) * quadratic_bezier(p0, p1, p2, t) + t * quadratic_bezier(p1, p2, p3, t);
}

double quadratic_bezier(double p0, double p1, double p2, double t) {
    return p1 + (1 - t) * (1 - t) * (p0 - p1) + t * t * (p2 - p1);
}