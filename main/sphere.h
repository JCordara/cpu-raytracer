#ifndef SPHERE_H
#define SPHERE_H

#include "../lib/vex3d.h"
#include "../lib/optional.h"
#include "shape.h"

/**
 * Contains the necessary information to define a sphere in 3D space. Includes
 * center of sphere and it's radius. Provides a method to calculate the 
 * intersection of a given ray with itself.
 */
class Sphere : public Shape<Sphere> {
private:

    vec3 _center;
    float _radius;

public:

    Sphere() = default;
    Sphere(const vec3& center, float radius, const Material& material);

    opt<Intersection> check_intersection(const Ray& ray) const;
    
    vec3 center();
    float radius();
    
    void set_center(vec3 new_center);
    void set_radius(float new_radius);

    Sphere(const Sphere& other) = default;
    Sphere& operator=(const Sphere& rhs) = default;
    
};

#endif // SPHERE_H
