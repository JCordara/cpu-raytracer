#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "../lib/vex3d.h"

/**
 * Stores information about ray-object intersection. Relevant information
 * includes the point of intersection, the object normal at the point of 
 * intersection, and the color of the object at the point of intersection.
 */
class Intersection {
public:

    // TODO: Move to private and add getters/setters
    vec3 normal;
    vec3 color;
    vec3 point;

    // TODO: Implement optional datatype to replace functionality of this field
    bool valid;

    Intersection() = default;
    Intersection(vec3 point, vec3 normal, vec3 color);

    Intersection(const Intersection& other) = default;
    Intersection& operator=(const Intersection& rhs) = default;

    // Returns an invalid intersection (objects do not intersect)
    static Intersection none();
};

#endif // INTERSECTION_H
