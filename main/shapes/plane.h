#ifndef SHAPES_PLANE_H
#define SHAPES_PLANE_H

#include "../../lib/vex3d.h"
#include "../../lib/optional.h"
#include "shape.h"

/**
 * Contains the necessary information to define a plane in 3D space. Defined by
 * surface normal and height (extending infinitely). Constructed by origin and normal,
 * height is calculated in construction;
 */
class Plane : public Shape<Plane> {
private:

    vec3 _normal;
    float _height;
    vec3 _origin;

public:

    Plane() = default;
    Plane(const vec3& origin, const vec3& normal, const Material& material);

    opt<Intersection> check_intersection(const Ray& ray) const;
    
    vec3 normal();
    vec3 origin();
    
    void set_normal(const vec3& normal);
    void set_origin(const vec3& origin);

    Plane(const Plane& other) = default;
    Plane& operator=(const Plane& rhs) = default;
    
};

#endif // SHAPES_PLANE_H
