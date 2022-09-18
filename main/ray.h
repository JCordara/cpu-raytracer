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

public:

    // TODO: Move to private and add getters/setters
    vec3 origin;
    vec3 direction;

    Ray(const vec3& origin, const vec3& direction);

    // Lazy calculation of normalized direction
    vec3 normalized_dir();
    
};

#endif // RAY_H
