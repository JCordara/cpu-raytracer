#include "intersection.h"

Intersection::Intersection(vec3 point, vec3 normal, vec3 color) : 
    point(point),
    normal(normal), 
    color(color), 
    valid(true) 
{}

Intersection Intersection::none() {
    Intersection empty_intersection;
    empty_intersection.valid = false;
    return empty_intersection;
}
