#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "../lib/vex3d.h"

/**
 * Stores information about ray-entity intersection. Relevant information
 * includes the point of intersection, the entity normal at the point of 
 * intersection, and the color of the entity at the point of intersection.
 */
class Intersection {
private:

    vec3 _normal;
    vec3 _color;
    vec3 _point;

public:
    // TODO: Implement optional datatype to replace functionality of this field
    bool valid;

    Intersection() = default;
    Intersection(vec3 point, vec3 normal, vec3 color);

    Intersection(const Intersection& other) = default;
    Intersection& operator=(const Intersection& rhs) = default;

    vec3 get_normal();
    vec3 get_color();
    vec3 get_point();
    void set_normal(const vec3& new_normal);
    void set_color(const vec3& new_color);
    void set_point(const vec3& new_point);

    // Returns an invalid intersection (ray and entity do not intersect)
    static Intersection none();
};

#endif // INTERSECTION_H
