#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "../lib/vex3d.h"
#include "material.h"

/**
 * Stores information about ray-entity intersection. Relevant information
 * includes the point of intersection, the entity normal at the point of 
 * intersection, and the color of the entity at the point of intersection.
 */
class Intersection {
private:

    vec3 _normal;
    vec3 _point;
    vec3 _direction;
    float _dist_sqr;
    const Material& _material;

public:

    Intersection();
    Intersection(
        const vec3& point, 
        const vec3& normal, 
        const vec3& direction, 
        float dist_sqr,
        const Material& material
    );

    Intersection(const Intersection& other) = default;

    const vec3& normal() const;
    const vec3& point() const;
    const vec3& direction() const;
    const float& dist_sqr() const;
    const Material& material() const;
    void set_normal(const vec3& new_normal);
    void set_point(const vec3& new_point);
    void set_direction(const vec3& new_direction);
    void set_dist_sqr(const float& new_dist_sqr);

};

#endif // INTERSECTION_H
