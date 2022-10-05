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
    vec3 _direction;
    float _dist_sqr;

public:

    Intersection() = default;
    Intersection(
        const vec3& point, 
        const vec3& normal, 
        const vec3& color, 
        const vec3& direction, 
        float dist_sqr);

    Intersection(const Intersection& other) = default;
    Intersection& operator=(const Intersection& rhs) = default;

    const vec3& normal() const;
    const vec3& color() const;
    const vec3& point() const;
    const vec3& direction() const;
    const float& dist_sqr() const;
    void set_normal(const vec3& new_normal);
    void set_color(const vec3& new_color);
    void set_point(const vec3& new_point);
    void set_direction(const vec3& new_direction);
    void set_dist_sqr(const float& new_dist_sqr);

};

#endif // INTERSECTION_H
