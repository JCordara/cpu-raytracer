#ifndef RAY_H
#define RAY_H

#include "../lib/vex3d.h"

/**
 * Contains information to define a ray in 3D space. Includes point of origin 
 * and direction. Normalized direction can be obtained through a lazy 
 * calculation.
 */
class Ray {
private:

    vec3 _direction_normalized;
    vec3 _origin;
    vec3 _direction;

public:

    Ray(const vec3& origin, const vec3& direction);

    // Lazy calculation of normalized direction
    vec3 normalized_dir();

    vec3 origin() const;
    vec3 direction() const;
    void set_origin(const vec3& new_origin);
    void set_direction(const vec3& new_direction);

};

#endif // RAY_H
