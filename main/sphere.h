#ifndef SPHERE_H
#define SPHERE_H

#include "../lib/vex3d.h"

class Ray;
class Intersection;

/**
 * Contains the necessary information to define a sphere in 3D space. Includes
 * origin (center) of sphere and radius. Provides a method to calculate the 
 * intersection of a given ray with itself.
 */
class Sphere {
public:

    // TODO: Move to private and add any appropriate getters/setters
    vec3 origin;
    float radius;
    float radius_sqr;
    vec3 color;

    Sphere() = default;
    Sphere(const vec3& origin, float radius, const vec3& color);

    Intersection check_intersection(const Ray& ray) const;
    
    Sphere(const Sphere& other) = default;
    Sphere& operator=(const Sphere& rhs) = default;
    
};

#endif // SPHERE_H
